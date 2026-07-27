#include "ArchicadArtifactRootObjectBuilder.h"

#include <chrono>
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <unordered_set>

#include "ArchiCadApiException.h"
#include "ArchicadObject.h"
#include "ArtefactSessionLog.h"
#include "ArtifactUploader.h"
#include "BundleWriter.h"
#include "Connector.h"
#include "ConverterUtils.h"
#include "SgeoEncoder.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "Utf8Path.h"
#include "WinHttpClient.h"

namespace
{
    // Mutable state threaded through the emit walk.
    //
    // Beyond the interning caches it collects the object->object edges that CANNOT be
    // written during the walk: an edge may only be emitted once both endpoints are known
    // to be sent objects, and the far endpoint may not have been reached yet (or may not
    // be in the selection at all). Interning an unsent guid would mint a phantom object
    // row with no properties and no geometry, so these are resolved in a second pass
    // against objectKByAppId. Mirrors the Revit builder's objectKsByElementUniqueId.
    struct EmitContext
    {
        std::unordered_map<int, int> materialCache;          // Modeler material index -> MATERIAL node K
        std::unordered_set<std::string> seenDefinitions;     // definitionId whose geometry is written
        std::unordered_map<std::string, int> objectKByAppId; // every emitted object, by applicationId

        // (hosted element guid, host element guid) — door/window -> wall, skylight -> roof/shell.
        std::vector<std::pair<std::string, std::string>> hostedPairs;

        // (zone guid, its spatial relations) and (opening guid, the two zones it connects).
        std::vector<std::pair<std::string, ArchicadRoomTopology>> zoneTopology;
        std::vector<std::pair<std::string, ArchicadRoomTopology>> openingTopology;
    };

    // Resolves (and caches) the MATERIAL node for a Modeler material index.
    int GetOrAddMaterialNode(BundleWriter& writer, std::unordered_map<int, int>& cache, int materialIndex)
    {
        auto it = cache.find(materialIndex);
        if (it != cache.end())
            return it->second;

        Material material = CONNECTOR.GetHostToSpeckleConverter().GetModelMaterial(materialIndex);
        const int argb = static_cast<int>(material.diffuse);
        const int k = writer.AddMaterial(
            std::to_string(materialIndex), material.name, argb, material.opacity, material.metalness, material.roughness);
        cache.emplace(materialIndex, k);
        return k;
    }

    // Emits the display geometry for an object as an INSTANCE of a shared DEFINITION.
    // The definition (its local-space geometry + material edges) is written once per
    // definitionId; every placement adds only its own INSTANCE node + DISPLAY_INSTANCE edge.
    void EmitInstance(BundleWriter& writer, EmitContext& ctx, int objK, const ArchicadObject& obj)
    {
        const std::string& definitionId = obj.instance.definitionId;
        const int defK = writer.AddDefinition(definitionId, obj.name.empty() ? definitionId : obj.name);

        // Definition geometry is emitted exactly once. Geometry ids are deterministic per
        // definition ("def:{id}:{i}") so AddGeometrySgeo interns them stably across placements.
        if (ctx.seenDefinitions.insert(definitionId).second)
        {
            int ord = 0;
            for (const auto& mesh : obj.instance.localBody.meshes)
            {
                const std::string geometryAppId = "def:" + definitionId + ":" + std::to_string(ord);
                const auto sgeo = SgeoEncoder::EncodeMesh(mesh.vertices, mesh.faces, mesh.colors, mesh.units);
                const int geometryK = writer.AddGeometrySgeo(geometryAppId, sgeo);
                writer.Defines(defK, geometryK, ord);

                const int materialK = GetOrAddMaterialNode(writer, ctx.materialCache, mesh.materialIndex);
                writer.HasMaterial(geometryK, materialK);
                ord++;
            }
        }

        // One INSTANCE per placement, keyed by the element's own applicationId.
        const int instK = writer.AddInstance(obj.applicationId, defK, obj.instance.transform, "m");
        writer.DisplayInstance(objK, instK, 0);
    }

    // Emits one ArchicadObject (and recursively its children) into the bundle.
    // Returns the object's dense K.
    int EmitObject(BundleWriter& writer, EmitContext& ctx, const ArchicadObject& obj, bool isTopLevel)
    {
        const int objK = writer.InternObject(obj.applicationId);
        ctx.objectKByAppId[obj.applicationId] = objK;

        // Deferred to the second pass — the host may be emitted later in the loop, or not
        // be in the selection at all.
        if (!obj.hostElementId.empty())
            ctx.hostedPairs.emplace_back(obj.applicationId, obj.hostElementId);

        if (!obj.roomInfo.occupantElementIds.empty() || !obj.roomInfo.boundingElementIds.empty())
            ctx.zoneTopology.emplace_back(obj.applicationId, obj.roomInfo);
        if (!obj.roomInfo.fromRoomId.empty() && !obj.roomInfo.toRoomId.empty())
            ctx.openingTopology.emplace_back(obj.applicationId, obj.roomInfo);

        // Root scalars mirror the eav root-scalar fields the SDK indexes
        // (speckle_type/name/type/level/units — same set Revit emits, minus category/family).
        std::vector<std::pair<std::string, nlohmann::json>> rootScalars;
        rootScalars.emplace_back("speckle_type", obj.speckle_type);
        if (!obj.name.empty())
            rootScalars.emplace_back("name", obj.name);
        if (!obj.type.empty())
            rootScalars.emplace_back("type", obj.type);
        if (!obj.level.empty())
            rootScalars.emplace_back("level", obj.level);
        rootScalars.emplace_back("units", "m");
        writer.AddProperties(obj.applicationId, obj.properties, rootScalars);

        if (isTopLevel && !obj.level.empty())
        {
            const int levelK = writer.AddLevel(
                std::to_string(obj.levelInfo.floorId), obj.level, obj.levelInfo.elevation);
            writer.OnLevel(objK, levelK);
        }

        // Layer membership -> CONTAINER(subtype "Collection") + IN_COLLECTION, the authored
        // scene-tree axis. Archicad layers are flat, so the container never gets a parent.
        // Children inherit the parent's layer (openings take their host's), so only top-level
        // objects carry the edge — same rule as ON_LEVEL above.
        if (isTopLevel && !obj.layerInfo.id.empty())
        {
            const int layerK = writer.AddCollection(obj.layerInfo.id, obj.layerInfo.name, nullptr, "Collection");
            writer.InCollection(objK, layerK, 0);
        }

        // Group membership -> CONTAINER(subtype "Group") + IN_GROUP. A SEPARATE axis from
        // IN_COLLECTION above: an element keeps its layer AND its group, and the receive side
        // treats the two differently (collection is last-wins because it IS the scene tree;
        // groups are multi-valued). Groups are emitted FLAT for now — the immediate group only,
        // no parent chain; see the plan's open questions.
        if (isTopLevel && !obj.groupId.empty())
        {
            const std::string groupName = CONNECTOR.GetHostToSpeckleConverter().GetGroupDisplayName(obj.groupId);
            const int groupK = writer.AddContainer(obj.groupId, groupName, nullptr, "Group");
            writer.InGroup(objK, groupK, 0);
        }

        if (obj.instance.valid)
        {
            // Instanced GDL/library-part object: shared DEFINITION + per-placement INSTANCE.
            EmitInstance(writer, ctx, objK, obj);
        }
        else
        {
            // Display geometry: deterministic per-mesh ids "{elementGuid}:{i}" (the v1 path used a
            // random GUID per mesh, which made material bindings fragile — fixed here for good).
            int ord = 0;
            for (const auto& mesh : obj.displayValue.meshes)
            {
                const std::string geometryAppId = obj.applicationId + ":" + std::to_string(ord);
                const auto sgeo = SgeoEncoder::EncodeMesh(mesh.vertices, mesh.faces, mesh.colors, mesh.units);
                const int geometryK = writer.AddGeometrySgeo(geometryAppId, sgeo);
                writer.Display(objK, geometryK, ord);

                const int materialK = GetOrAddMaterialNode(writer, ctx.materialCache, mesh.materialIndex);
                writer.HasMaterial(geometryK, materialK);
                ord++;
            }
        }

        // Hosted/nested children (beam & column segments today) -> SUBELEMENT edges.
        int subOrd = 0;
        for (const auto& child : obj.elements)
        {
            const int childK = EmitObject(writer, ctx, child, false);
            writer.Subelement(objK, childK, subOrd++);
        }

        return objK;
    }

    // Second pass: object->object edges whose far endpoint could only be resolved once the
    // whole selection had been emitted. Every edge is guarded on BOTH endpoints being sent
    // objects — an opening whose wall is not in the selection simply gets no edge, rather
    // than a dangling reference into an object that carries no data.
    void EmitDeferredTopology(BundleWriter& writer, const EmitContext& ctx)
    {
        // Resolves an applicationId to its object K, or nullptr when that element was not
        // among the sent objects.
        const auto resolve = [&ctx](const std::string& appId) -> const int*
        {
            const auto it = ctx.objectKByAppId.find(appId);
            return it == ctx.objectKByAppId.end() ? nullptr : &it->second;
        };

        for (const auto& [hostedAppId, hostAppId] : ctx.hostedPairs)
        {
            const int* hosted = resolve(hostedAppId);
            const int* host = resolve(hostAppId);
            if (hosted != nullptr && host != nullptr)
                writer.HostedOn(*hosted, *host);
        }

        for (const auto& [zoneAppId, topology] : ctx.zoneTopology)
        {
            const int* zoneK = resolve(zoneAppId);
            if (zoneK == nullptr)
                continue;

            for (const auto& occupantId : topology.occupantElementIds)
            {
                if (const int* occupantK = resolve(occupantId))
                    writer.InRoom(*occupantK, *zoneK, 0);
            }

            int boundsOrd = 0;
            for (const auto& boundingId : topology.boundingElementIds)
            {
                if (const int* boundingK = resolve(boundingId))
                    writer.Bounds(*boundingK, *zoneK, boundsOrd++);
            }
        }

        // Zone adjacency: the two zones an opening joins, scoped by the opening itself so a
        // consumer can tell WHICH door connects a given pair (CONNECTS_TO's ord is a scope
        // tag, not an ordinal).
        for (const auto& [openingAppId, topology] : ctx.openingTopology)
        {
            const int* openingK = resolve(openingAppId);
            const int* fromK = resolve(topology.fromRoomId);
            const int* toK = resolve(topology.toRoomId);
            if (openingK != nullptr && fromK != nullptr && toK != nullptr)
                writer.ConnectsTo(*fromK, *toK, *openingK);
        }
    }
}

NativeSendResult ArchicadArtifactRootObjectBuilder::BuildAndUpload(
    const std::vector<std::string>& elementIds,
    bool includeProperties,
    const std::string& serverUrl,
    const std::string& token,
    const std::string& projectId,
    const std::string& modelId,
    std::vector<SendConversionResult>& conversionResults)
{
    auto http = std::make_shared<WinHttpClient>();
    ArtifactUploader uploader(http, serverUrl, token, projectId);
    IProcessWindow& processWindow = CONNECTOR.GetProcessWindow();

    // 1. Create the ingestion. The server MUST pre-allocate the versionId — it is baked
    //    into the parquet filenames and used as the commit PK at complete. Failures
    //    propagate as-is (auth, network, old server) — there is no legacy fallback.
    //    The process window was Init'd by SendBridge (phase plan documented there).
    processWindow.SetNextProcessPhase("Preparing upload", 1);
    IngestionInfo ingestion = uploader.CreateIngestion(
        modelId,
        "Sending from Archicad",
        "archicad",
        CONNECTOR.GetHostToSpeckleConverter().GetHostAppReleaseInfo());
    if (ingestion.versionId.empty())
    {
        throw std::runtime_error(
            "The server did not pre-allocate a version id for this ingestion; "
            "the Speckle 4.0 artefact upload path requires the v2 data endpoints.");
    }

    ArtefactSessionLog session("Archicad", projectId, ingestion.versionId);

    try
    {
        const std::filesystem::path outputDir =
            std::filesystem::temp_directory_path() / "Speckle" / "artifacts" / ingestion.versionId;
        BundleWriter writer(Utf8Path::ToUtf8(outputDir), ingestion.versionId);

        // 2. Collect + emit in one pass (ACAPI main thread). The SendCacheScope
        //    keeps per-send invariants (3D model + GUID index, stories, attribute
        //    names, ...) cached across elements for the duration of the loop.
        session.BeginPhase("CollectAndWrite");
        ConverterUtils::SendCacheScope sendCacheScope;

        // Drop sub-elements whose hierarchical parent is also selected — they are emitted as
        // that parent's SUBELEMENT children, so sending them again at top level would
        // duplicate their geometry and properties. A single element-type filter returns both
        // tiers ("CurtainWall" -> the wall AND its frames/panels/...), which is exactly when
        // this bites.
        const std::vector<std::string> topLevelIds =
            CONNECTOR.GetHostToSpeckleConverter().FilterOutHierarchicalChildren(elementIds);
        const size_t foldedIntoParents = elementIds.size() - topLevelIds.size();
        session.SetStat("foldedIntoParents", static_cast<long long>(foldedIntoParents));

        processWindow.SetNextProcessPhase("Converting elements", static_cast<int>(topLevelIds.size()));
        EmitContext ctx;
        int elemCount = 0;
        for (const auto& elemId : topLevelIds)
        {
            elemCount++;
            processWindow.SetProcessValue(elemCount);
            SendConversionResult conversionResult{};
            const auto objStart = std::chrono::steady_clock::now();

            try
            {
                auto archicadObject =
                    CONNECTOR.GetHostToSpeckleConverter().GetArchicadObject(elemId, conversionResult, includeProperties);
                EmitObject(writer, ctx, archicadObject, true);

                const double ms =
                    std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - objStart).count();
                session.RecordObject(archicadObject.applicationId, archicadObject.type, "SUCCESS", "", ms);
            }
            catch (const ArchiCadApiException& ae)
            {
                conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
                conversionResult.error.message = ae.what();
                session.RecordObject(elemId, "", "ERROR", ae.what(), 0);
            }
            catch (const SpeckleConversionException& se)
            {
                conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
                conversionResult.error.message = se.what();
                session.RecordObject(elemId, "", "ERROR", se.what(), 0);
            }

            conversionResults.push_back(conversionResult);

            if (processWindow.IsProcessCanceled())
                throw UserCancelledException("The user cancelled the send operation");
        }

        // 3. Object->object topology whose endpoints could only be resolved after the whole
        //    selection was emitted (HOSTED_ON). Never fails the send.
        EmitDeferredTopology(writer, ctx);

        // 4. Default explorer projection: Story (ON_LEVEL) -> Layer (IN_COLLECTION) ->
        //    Element type (eav "type"). Layer sits between them because that is how
        //    Archicad users navigate a storey; the type tier stays innermost.
        writer.AddSceneView(0, "Default", true, {
            { "rel", std::to_string(static_cast<int>(bundlespec::Rel::ON_LEVEL)) },
            { "rel", std::to_string(static_cast<int>(bundlespec::Rel::IN_COLLECTION)) },
            { "eav", "type" },
        });

        const int objectCount = writer.ObjectCount();
        session.SetStat("objects", objectCount);
        session.EndPhase();

        // 5. Flush the parquet bundle (one tick per finalized table).
        session.BeginPhase("WriteParquet");
        processWindow.SetNextProcessPhase("Writing bundle", BundleWriter::TableCount());
        auto files = writer.Complete([&](int done, int)
        {
            processWindow.SetProcessValue(done);
            if (processWindow.IsProcessCanceled())
                throw UserCancelledException("The user cancelled the send operation");
        });
        session.SetStat("files", static_cast<long long>(files.size()));
        session.EndPhase();

        // 6. Upload: sign -> presigned PUT per file -> complete (creates the version).
        //    UploadFiles drives the "Uploading" (KiB-granular, cancellable) and
        //    "Creating version" phases itself.
        session.BeginPhase("Upload");
        const std::string rootId = "binary-" + ingestion.versionId;
        const std::string versionId = uploader.UploadFiles(
            ingestion.ingestionId, ingestion.versionId, files, rootId, objectCount, &processWindow);
        session.EndPhase();

        NativeSendResult result;
        result.versionId = versionId;
        result.objectCount = objectCount;
        return result;
    }
    catch (const UserCancelledException&)
    {
        uploader.FailWithCancel(ingestion.ingestionId, "User cancelled the send");
        throw;
    }
    catch (const std::exception& e)
    {
        session.Fail(e.what());
        uploader.FailWithError(ingestion.ingestionId, e.what());
        throw;
    }
}
