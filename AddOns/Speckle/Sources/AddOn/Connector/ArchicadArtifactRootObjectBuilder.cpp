#include "ArchicadArtifactRootObjectBuilder.h"

#include <chrono>
#include <filesystem>
#include <map>
#include <memory>

#include "ArchiCadApiException.h"
#include "ArchicadObject.h"
#include "ArtefactSessionLog.h"
#include "ArtifactUploader.h"
#include "BundleWriter.h"
#include "Connector.h"
#include "SgeoEncoder.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "WinHttpClient.h"

namespace
{
    // Resolves (and caches) the MATERIAL node for a Modeler material index.
    int GetOrAddMaterialNode(BundleWriter& writer, std::map<int, int>& cache, int materialIndex)
    {
        auto it = cache.find(materialIndex);
        if (it != cache.end())
            return it->second;

        Material material = CONNECTOR.GetHostToSpeckleConverter().GetModelMaterial(materialIndex);
        const int argb = static_cast<int>(material.diffuse);
        const int k = writer.AddMaterial(
            std::to_string(materialIndex), argb, material.opacity, material.metalness, material.roughness);
        cache.emplace(materialIndex, k);
        return k;
    }

    // Emits one ArchicadObject (and recursively its children) into the bundle.
    // Returns the object's dense K.
    int EmitObject(
        BundleWriter& writer,
        std::map<int, int>& materialCache,
        const ArchicadObject& obj,
        bool isTopLevel)
    {
        const int objK = writer.InternObject(obj.applicationId);

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

        // Display geometry: deterministic per-mesh ids "{elementGuid}:{i}" (the v1 path used a
        // random GUID per mesh, which made material bindings fragile — fixed here for good).
        int ord = 0;
        for (const auto& mesh : obj.displayValue.meshes)
        {
            const std::string geometryAppId = obj.applicationId + ":" + std::to_string(ord);
            const auto sgeo = SgeoEncoder::EncodeMesh(mesh.vertices, mesh.faces, mesh.colors, mesh.units);
            const int geometryK = writer.AddGeometrySgeo(geometryAppId, sgeo);
            writer.Display(objK, geometryK, ord);

            const int materialK = GetOrAddMaterialNode(writer, materialCache, mesh.materialIndex);
            writer.HasMaterial(geometryK, materialK);
            ord++;
        }

        // Hosted/nested children (beam & column segments today) -> SUBELEMENT edges.
        int subOrd = 0;
        for (const auto& child : obj.elements)
        {
            const int childK = EmitObject(writer, materialCache, child, false);
            writer.Subelement(objK, childK, subOrd++);
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
    //    into the parquet filenames and used as the commit PK at complete. Servers without
    //    the v2 data endpoints fail here -> legacy browser fallback.
    IngestionInfo ingestion;
    try
    {
        ingestion = uploader.CreateIngestion(
            modelId,
            "Sending from Archicad",
            "archicad",
            CONNECTOR.GetHostToSpeckleConverter().GetHostAppReleaseInfo());
    }
    catch (const std::exception& e)
    {
        throw ServerNotSupportedException(
            std::string("Model ingestion API unavailable (") + e.what() + ")");
    }
    if (ingestion.versionId.empty())
    {
        throw ServerNotSupportedException(
            "The server did not pre-allocate a version id for this ingestion; "
            "the Speckle 4.0 artefact upload path requires the v2 data endpoints.");
    }

    ArtefactSessionLog session("Archicad", projectId, ingestion.versionId);

    try
    {
        const std::filesystem::path outputDir =
            std::filesystem::temp_directory_path() / "Speckle" / "artifacts" / ingestion.versionId;
        BundleWriter writer(outputDir.string(), ingestion.versionId);

        // 2. Collect + emit in one pass (ACAPI main thread).
        session.BeginPhase("CollectAndWrite");
        CONNECTOR.GetProcessWindow().Init("Converting elements", static_cast<int>(elementIds.size()));
        std::map<int, int> materialCache;
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
                EmitObject(writer, materialCache, archicadObject, true);

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

        // 3. Default explorer projection: Story (ON_LEVEL) -> Element type (eav "type") —
        //    the same hierarchy the old nested Level/ElementTypeCollection tree encoded.
        writer.AddSceneView(0, "Default", true, {
            { "rel", std::to_string(static_cast<int>(bundlespec::Rel::ON_LEVEL)) },
            { "eav", "type" },
        });

        const int objectCount = writer.ObjectCount();
        session.SetStat("objects", objectCount);
        session.EndPhase();

        // 4. Flush the parquet bundle.
        session.BeginPhase("WriteParquet");
        CONNECTOR.GetProcessWindow().SetNextProcessPhase("Writing bundle", 1);
        auto files = writer.Complete();
        session.SetStat("files", static_cast<long long>(files.size()));
        session.EndPhase();

        // 5. Upload: sign -> presigned PUT per file -> complete (creates the version).
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
