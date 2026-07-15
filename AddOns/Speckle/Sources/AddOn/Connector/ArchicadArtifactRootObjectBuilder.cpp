#include "ArchicadArtifactRootObjectBuilder.h"

#include <chrono>
#include <filesystem>
#include <map>
#include <memory>

#include "ArchiCadApiException.h"
#include "ArchicadObject.h"
#include "ArtefactSessionLog.h"
#include "ArtifactUploader.h"
#include "Connector.h"
#include "JsonToPDict.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "WinHttpClient.h"

// Shared bundle producer (speckle-bundle-spec cpp package) — the same writer the
// converters use; DuckDB is gone. The writer mints Ks unconditionally, so the dedup
// maps (geometry app-id, material index, level key) live here in the feeder.
#include "bundle_writer.h"
#include "envelope_catalog.h"
#include "sgeo.h"

namespace
{
    // Default geometry shard cap — the SDK's SPECKLE_GEOMETRY_SHARD_MB=1536 (1.5 GiB
    // uncompressed), same as the converters. Bundles under the cap keep the single
    // canonical {base}.geometries.parquet name.
    constexpr int64_t kGeomShardCapBytes = 1536LL * 1024 * 1024;

    struct DedupMaps
    {
        std::map<int, int> materialK;          // Modeler material index -> node K
        std::map<std::string, int> levelK;     // floorId key -> node K
        std::map<std::string, int> geometryK;  // geometry app id -> geometry K
    };

    // Resolves (and caches) the MATERIAL node for a Modeler material index.
    int GetOrAddMaterialNode(BundleWriter& writer, DedupMaps& maps, int materialIndex)
    {
        auto it = maps.materialK.find(materialIndex);
        if (it != maps.materialK.end())
            return it->second;

        Material material = CONNECTOR.GetHostToSpeckleConverter().GetModelMaterial(materialIndex);
        const int argb = static_cast<int>(material.diffuse);
        // Material nodes carry no name (matches the previous writer); the receive side
        // falls back to "Speckle Material <K>". Roughness is real data (1 − shining/100);
        // metalness is always 0 in Archicad and stays the shared writer's fixed 0.0.
        const int k = writer.addNode(
            bundlespec::NodeKind::MATERIAL, nullptr, -1, nullptr, nullptr, nullptr,
            true, argb, material.opacity, material.roughness);
        maps.materialK.emplace(materialIndex, k);
        return k;
    }

    void AddProperties(
        BundleWriter& writer,
        int objK,
        const nlohmann::json& properties,
        const std::vector<std::pair<std::string, std::string>>& rootScalars)
    {
        std::vector<std::pair<std::string, PVal>> roots;
        roots.reserve(rootScalars.size());
        for (const auto& kv : rootScalars)
            roots.emplace_back(kv.first, PVal::Str(kv.second));

        auto dict = JsonToPDict::Convert(properties);

        // Archicad property groups are user-definable — disable the Revit-shaped
        // key special-cases so e.g. a group named "Material Quantities" survives.
        eav::WalkOptions opts;
        opts.skipTypeParamsStructure = false;
        opts.materialQuantitiesSpecialCase = false;

        std::vector<EavRow> rows;
        eav::flatten(*dict, roots, nullptr, rows, opts);
        writer.writeInstanceEav(objK, rows);
    }

    // Emits one ArchicadObject (and recursively its children) into the bundle.
    // Returns the object's dense K.
    int EmitObject(
        BundleWriter& writer,
        DedupMaps& maps,
        const ArchicadObject& obj,
        bool isTopLevel)
    {
        const int objK = writer.internObject(obj.applicationId);

        // Root scalars mirror the eav root-scalar fields the SDK indexes
        // (speckle_type/name/type/level/units — same set Revit emits, minus category/family).
        std::vector<std::pair<std::string, std::string>> rootScalars;
        rootScalars.emplace_back("speckle_type", obj.speckle_type);
        if (!obj.name.empty())
            rootScalars.emplace_back("name", obj.name);
        if (!obj.type.empty())
            rootScalars.emplace_back("type", obj.type);
        if (!obj.level.empty())
            rootScalars.emplace_back("level", obj.level);
        rootScalars.emplace_back("units", "m");
        AddProperties(writer, objK, obj.properties, rootScalars);

        if (isTopLevel && !obj.level.empty())
        {
            const std::string levelKey = std::to_string(obj.levelInfo.floorId);
            auto lk = maps.levelK.find(levelKey);
            int levelK;
            if (lk != maps.levelK.end())
                levelK = lk->second;
            else
            {
                levelK = writer.addLevelNode(&obj.level, obj.levelInfo.elevation);
                maps.levelK.emplace(levelKey, levelK);
            }
            writer.addRel(static_cast<int>(bundlespec::Rel::ON_LEVEL), objK, levelK, 0);
        }

        // Display geometry: deterministic per-mesh ids "{elementGuid}:{i}" (the v1 path used a
        // random GUID per mesh, which made material bindings fragile — fixed here for good).
        int ord = 0;
        for (const auto& mesh : obj.displayValue.meshes)
        {
            const std::string geometryAppId = obj.applicationId + ":" + std::to_string(ord);
            int geometryK;
            auto gk = maps.geometryK.find(geometryAppId);
            if (gk != maps.geometryK.end())
                geometryK = gk->second;
            else
            {
                const auto blob = sgeo::encodeMesh(
                    mesh.vertices, mesh.faces, units::code(mesh.units), mesh.colors);
                const std::string id = sgeo::sha256hex(blob.data(), blob.size());
                geometryK = writer.addGeometry(id, blob.data(), static_cast<int64_t>(blob.size()));
                maps.geometryK.emplace(geometryAppId, geometryK);
            }
            writer.addRel(static_cast<int>(bundlespec::Rel::DISPLAY), objK, geometryK, ord);

            const int materialK = GetOrAddMaterialNode(writer, maps, mesh.materialIndex);
            writer.addRel(static_cast<int>(bundlespec::Rel::HAS_MATERIAL), geometryK, materialK, 0);
            ord++;
        }

        // Hosted/nested children (beam & column segments today) -> SUBELEMENT edges.
        int subOrd = 0;
        for (const auto& child : obj.elements)
        {
            const int childK = EmitObject(writer, maps, child, false);
            writer.addRel(static_cast<int>(bundlespec::Rel::SUBELEMENT), objK, childK, subOrd++);
        }

        return objK;
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

    // 1. Create the ingestion. The server MUST pre-allocate the versionId — it is baked
    //    into the parquet filenames and used as the commit PK at complete. Failures
    //    propagate as-is (auth, network, old server) — there is no legacy fallback.
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
        std::filesystem::create_directories(outputDir);
        BundleWriter writer(outputDir.string(), ingestion.versionId, kGeomShardCapBytes);
        if (!writer.ok())
            throw std::runtime_error("BundleWriter: failed to create the parquet bundle in " + outputDir.string());

        // 2. Collect + emit in one pass (ACAPI main thread).
        session.BeginPhase("CollectAndWrite");
        CONNECTOR.GetProcessWindow().Init("Converting elements", static_cast<int>(elementIds.size()));
        DedupMaps maps;
        int elemCount = 0;
        for (const auto& elemId : elementIds)
        {
            elemCount++;
            CONNECTOR.GetProcessWindow().SetProcessValue(elemCount);
            SendConversionResult conversionResult{};
            const auto objStart = std::chrono::steady_clock::now();

            try
            {
                auto archicadObject =
                    CONNECTOR.GetHostToSpeckleConverter().GetArchicadObject(elemId, conversionResult, includeProperties);
                EmitObject(writer, maps, archicadObject, true);

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

            if (CONNECTOR.GetProcessWindow().IsProcessCanceled())
                throw UserCancelledException("The user cancelled the send operation");
        }

        const int objectCount = static_cast<int>(writer.objectCount());
        session.SetStat("objects", objectCount);
        session.EndPhase();

        // 3. Flush the parquet bundle + the constant catalog sidecars + the default
        //    explorer projection: Story (ON_LEVEL) -> Element type (eav "type") — the
        //    same hierarchy the old nested Level/ElementTypeCollection tree encoded.
        session.BeginPhase("WriteParquet");
        CONNECTOR.GetProcessWindow().SetNextProcessPhase("Writing bundle", 1);
        writer.finalize();
        if (!writer.ok())
            throw std::runtime_error("BundleWriter: failed to write the parquet bundle");
        envcat::writeCatalogTables(outputDir.string(), ingestion.versionId, "Speckle Archicad BundleWriter");
        envcat::writeSceneViewTiers(outputDir.string(), ingestion.versionId, {
            { "rel", std::to_string(static_cast<int>(bundlespec::Rel::ON_LEVEL)) },
            { "eav", "type" },
        });

        // Collect the written files for the uploader (fileName -> full path). The dir
        // is exclusive to this versionId, so everything in it belongs to the bundle.
        std::map<std::string, std::string> files;
        for (const auto& entry : std::filesystem::directory_iterator(outputDir))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".parquet")
                files[entry.path().filename().string()] = entry.path().string();
        }
        session.SetStat("files", static_cast<long long>(files.size()));
        session.EndPhase();

        // 4. Upload: sign -> presigned PUT per file -> complete (creates the version).
        session.BeginPhase("Upload");
        CONNECTOR.GetProcessWindow().SetNextProcessPhase("Uploading", static_cast<int>(files.size()));
        const std::string rootId = "binary-" + ingestion.versionId;
        const std::string versionId =
            uploader.UploadFiles(ingestion.ingestionId, ingestion.versionId, files, rootId, objectCount);
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
