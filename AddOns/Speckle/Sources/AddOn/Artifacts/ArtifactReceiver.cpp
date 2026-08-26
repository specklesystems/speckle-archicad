#include "ArtifactReceiver.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <limits>
#include <map>
#include <random>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string_view>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#endif

#include "json.hpp"
#include "minipq_reader.h"

#include "GdlLibpartXml.h"
#include "SgeoDecoder.h"
#include "UserCancelledException.h"
#include "Utf8Path.h"

namespace fs = std::filesystem;
using nlohmann::json;

namespace
{
    // ── shared small helpers ─────────────────────────────────────────────────

    std::string TrimTrailingSlash(const std::string& url)
    {
        std::string result = url;
        while (!result.empty() && result.back() == '/')
            result.pop_back();
        return result;
    }

    double UnitsToMetersFactor(const std::string& units)
    {
        if (units == "m" || units.empty() || units == "none") return 1.0;
        if (units == "mm") return 0.001;
        if (units == "cm") return 0.01;
        if (units == "km") return 1000.0;
        if (units == "in") return 0.0254;
        if (units == "ft") return 0.3048;
        if (units == "yd") return 0.9144;
        if (units == "mi") return 1609.344;
        return 1.0;
    }

    std::string RandomDirName(size_t length)
    {
        static const char chars[] = "abcdefghijklmnopqrstuvwxyz1234567890";
        std::random_device rd;
        std::string out;
        out.reserve(length);
        for (size_t i = 0; i < length; i++)
            out.push_back(chars[rd() % (sizeof(chars) - 1)]);
        return out;
    }

    // Row-major 4x4 (translation in elements 3, 7, 11 — Speckle Transform layout).
    struct Mat4
    {
        double m[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
        bool isIdentity = true;

        static Mat4 Multiply(const Mat4& a, const Mat4& b)
        {
            Mat4 r;
            r.isIdentity = false;
            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {
                    double sum = 0;
                    for (int k = 0; k < 4; k++)
                        sum += a.m[row * 4 + k] * b.m[k * 4 + col];
                    r.m[row * 4 + col] = sum;
                }
            }
            return r;
        }

        void TransformPoint(double& x, double& y, double& z) const
        {
            const double tx = m[0] * x + m[1] * y + m[2] * z + m[3];
            const double ty = m[4] * x + m[5] * y + m[6] * z + m[7];
            const double tz = m[8] * x + m[9] * y + m[10] * z + m[11];
            const double tw = m[12] * x + m[13] * y + m[14] * z + m[15];
            if (tw != 0.0 && tw != 1.0)
            {
                x = tx / tw;
                y = ty / tw;
                z = tz / tw;
            }
            else
            {
                x = tx;
                y = ty;
                z = tz;
            }
        }
    };

    // "a,b,c,..." (16 row-major doubles) → Mat4 with the translation column
    // scaled from the transform's own units to meters.
    bool ParseTransform(const std::string& csv, const std::string& units, Mat4& out)
    {
        std::vector<double> values;
        values.reserve(16);
        std::stringstream ss(csv);
        std::string item;
        while (std::getline(ss, item, ','))
        {
            char* end = nullptr;
            const double v = std::strtod(item.c_str(), &end);
            if (end == item.c_str())
                return false;
            values.push_back(v);
        }
        if (values.size() != 16)
            return false;

        const double f = UnitsToMetersFactor(units);
        values[3] *= f;
        values[7] *= f;
        values[11] *= f;

        std::copy(values.begin(), values.end(), out.m);
        out.isIdentity = false;
        return true;
    }

    // ── minipq parquet reading helpers ───────────────────────────────────────
    // The bundle read side needs only column scans (plus one sort and a couple of
    // IN-filters, done in C++ below) — minipq_reader covers that with no DuckDB.

    // Opens a bundle parquet and resolves column names to indices up front.
    struct ParquetFile
    {
        minipq::Reader reader;
        std::vector<int> cols;    // same order as the requested names
        std::vector<int> optCols; // same order as optionalColumns; -1 when absent

        // Columns the spec added after a producer shipped are OPTIONAL: the spec's
        // additive-column contract requires consumers to read by name and tolerate
        // absence, so a bundle written before the column existed still loads.
        ParquetFile(const std::string& path, const std::vector<std::string>& columns,
                    const std::vector<std::string>& optionalColumns = {})
            : reader(path)
        {
            if (!reader.good)
                throw std::runtime_error("ArtifactReceiver: cannot read " + path);
            const auto& names = reader.columnNames();
            for (const auto& wanted : columns)
            {
                const auto it = std::find(names.begin(), names.end(), wanted);
                if (it == names.end())
                    throw std::runtime_error("ArtifactReceiver: " + path + " has no column '" + wanted + "'");
                cols.push_back(static_cast<int>(it - names.begin()));
            }
            for (const auto& wanted : optionalColumns)
            {
                const auto it = std::find(names.begin(), names.end(), wanted);
                optCols.push_back(it == names.end() ? -1 : static_cast<int>(it - names.begin()));
            }
        }

        // next() returns false at both EOF and decode error; tell them apart.
        bool Next(minipq::Batch& batch, const std::string& path)
        {
            if (reader.next(batch))
                return true;
            if (!reader.good)
                throw std::runtime_error("ArtifactReceiver: corrupt parquet file " + path);
            return false;
        }
    };

    // NULL -> "" (same contract the DuckDB-based reader had).
    std::string StrOrEmpty(const minipq::BytesArr& arr, std::int64_t row)
    {
        if (arr.IsNull(row))
            return "";
        const std::string_view v = arr.GetView(row);
        return std::string(v);
    }

    // ── external converter processes ─────────────────────────────────────────

#ifdef _WIN32
    struct ConverterProcess
    {
        HANDLE process = nullptr;
    };

    ConverterProcess StartConverter(
        const std::string& converterPath,
        const std::string& inputDir,
        const std::string& outputDir)
    {
        std::wstring cmd = L"\"" + fs::path(converterPath).wstring() + L"\" x2l \"" +
                           fs::path(inputDir).wstring() + L"\" \"" + fs::path(outputDir).wstring() + L"\"";

        STARTUPINFOW si{};
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi{};
        // CreateProcess may modify the command-line buffer.
        std::vector<wchar_t> cmdBuf(cmd.begin(), cmd.end());
        cmdBuf.push_back(L'\0');

        if (!CreateProcessW(
                nullptr, cmdBuf.data(), nullptr, nullptr, FALSE,
                CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
        {
            throw std::runtime_error(
                "Failed to start LP_XMLConverter (error " + std::to_string(GetLastError()) + ")");
        }
        CloseHandle(pi.hThread);
        return ConverterProcess{ pi.hProcess };
    }
#endif
}

ArtifactReceiver::ArtifactReceiver(
    std::shared_ptr<IHttpClient> http,
    const std::string& serverUrl,
    const std::string& token)
    : _http(std::move(http)), _serverUrl(TrimTrailingSlash(serverUrl)), _token(token)
{
}

std::string ArtifactReceiver::ResolveVersionId(
    const std::string& projectId,
    const std::string& modelId,
    const std::string& selectedVersionId)
{
    if (!selectedVersionId.empty())
        return selectedVersionId;

    json body;
    body["query"] =
        "query LatestVersion($projectId: String!, $modelId: String!) { "
        "project(id: $projectId) { model(id: $modelId) { versions(limit: 1) { items { id } } } } }";
    body["variables"] = { { "projectId", projectId }, { "modelId", modelId } };

    HttpResponse response = _http->PostJson(_serverUrl + "/graphql", body.dump(), _token);
    if (!response.IsSuccess())
        throw std::runtime_error("Could not resolve the latest version (HTTP " + std::to_string(response.statusCode) + ")");

    json parsed = json::parse(response.body);
    auto items = parsed["data"]["project"]["model"]["versions"]["items"];
    if (!items.is_array() || items.empty())
        throw std::runtime_error("The model has no versions to receive");
    return items[0]["id"].get<std::string>();
}

ArtifactReceiver::Result ArtifactReceiver::Receive(
    const std::string& projectId,
    const std::string& modelId,
    const std::string& versionId,
    const std::string& xmlConverterPath,
    IProcessWindow& processWindow)
{
#ifndef _WIN32
    throw std::runtime_error("Native artefact receive is Windows-only for now");
#else
    Result result;

    // ── working folders (same layout the desktop service used) ─────────────
    const char* appData = std::getenv("APPDATA");
    if (appData == nullptr)
        throw std::runtime_error("APPDATA is not set");
    const fs::path rootDir = fs::path(appData) / "Speckle" / "Archicad" / "receive_temp" / RandomDirName(16);
    const fs::path bundleDir = rootDir / "bundle";
    const fs::path outputDir = rootDir / "_output";
    fs::create_directories(bundleDir);
    fs::create_directories(outputDir);
    result.rootDir = rootDir.string();
    result.gsmFolder = outputDir.string();

    // ── 1. download the bundle files receive needs ──────────────────────────
    processWindow.SetNextProcessPhase("Downloading version data", 1);

    const std::string artifactsUrl =
        _serverUrl + "/api/v2/projects/" + projectId + "/models/" + modelId + "/versions/" + versionId + "/artifacts";
    HttpResponse listResponse = _http->Get(artifactsUrl, _token);
    if (!listResponse.IsSuccess())
    {
        throw std::runtime_error(
            "Could not list version artifacts (HTTP " + std::to_string(listResponse.statusCode) +
            ") — receiving non-4.0 versions is not supported by this connector");
    }

    json artifactList = json::parse(listResponse.body);
    const json& files = artifactList.contains("files") ? artifactList["files"] : artifactList;

    auto isNeeded = [](const std::string& name)
    {
        const bool geometries = name.find(".geometries") != std::string::npos && name.rfind(".parquet") != std::string::npos;
        const bool nodes = name.rfind(".envelope.nodes.parquet") != std::string::npos;
        const bool relations = name.rfind(".envelope.relations.parquet") != std::string::npos;
        const bool objects = name.rfind(".eav.objects.parquet") != std::string::npos;
        return geometries || nodes || relations || objects;
    };

    std::vector<std::string> geometryPaths;
    std::string nodesPath, relationsPath, objectsPath;
    int downloaded = 0;
    for (const auto& f : files)
    {
        const std::string name = f["name"].get<std::string>();
        if (!isNeeded(name))
            continue;
        const std::string localPath = Utf8Path::ToUtf8(bundleDir / name);
        HttpResponse dl = _http->GetToFile(f["url"].get<std::string>(), "", localPath);
        if (!dl.IsSuccess())
            throw std::runtime_error("Failed to download " + name + " (HTTP " + std::to_string(dl.statusCode) + ")");
        downloaded++;
        processWindow.SetProcessValue(downloaded);
        if (processWindow.IsProcessCanceled())
            throw UserCancelledException("The user cancelled the receive operation");

        if (name.find(".geometries") != std::string::npos)
            geometryPaths.push_back(localPath);
        else if (name.rfind(".envelope.nodes.parquet") != std::string::npos)
            nodesPath = localPath;
        else if (name.rfind(".envelope.relations.parquet") != std::string::npos)
            relationsPath = localPath;
        else if (name.rfind(".eav.objects.parquet") != std::string::npos)
            objectsPath = localPath;
    }

    if (geometryPaths.empty() || nodesPath.empty() || relationsPath.empty() || objectsPath.empty())
    {
        throw std::runtime_error(
            "This version has no Speckle 4.0 artefact bundle — it cannot be received by this connector");
    }

    // ── 2. read the bundle ───────────────────────────────────────────────────
    processWindow.SetNextProcessPhase("Reading version data", 1);

    std::map<int, std::string> appIdByObj;
    {
        ParquetFile f(objectsPath, { "object_index", "application_id" });
        minipq::Batch batch;
        while (f.Next(batch, objectsPath))
        {
            const auto objectIndex = minipq::i32(batch, f.cols[0]);
            const auto applicationId = minipq::bytes(batch, f.cols[1]);
            for (std::int64_t r = 0; r < batch.num_rows(); r++)
                appIdByObj[objectIndex.Value(r)] = StrOrEmpty(applicationId, r);
        }
    }

    // Relations we consume, by spec id:
    //   geometry   DISPLAY 1, SOLID 2, DEFINES 4, DISPLAY_INSTANCE 8, DEFINES_INSTANCE 9
    //   appearance HAS_MATERIAL 5, HAS_COLOR 6 (geometry plane)
    //              OBJECT_HAS_MATERIAL 26, OBJECT_HAS_COLOR 27 (object plane)
    //              NODE_HAS_MATERIAL 28, NODE_HAS_COLOR 29 (container plane)
    //   traversal  IN_COLLECTION 10 (object -> its container, for the container tier)
    //              PLACES 24 (member object -> its INSTANCE, the object<->node map)
    // SOLID went live and the appearance rels were split out of HAS_MATERIAL/HAS_COLOR
    // after this reader was written, so a bundle from Rhino/AutoCAD/SketchUp carried
    // colour and placement paint on edges we dropped on the floor.
    std::map<int, std::vector<int>> displayByObj;
    std::map<int, std::vector<int>> definesByDef;
    std::map<int, std::vector<int>> solidByObj;
    std::map<int, int> materialByGeom;
    std::map<int, int> colorByGeom;
    std::map<int, int> materialByObj;
    std::map<int, int> colorByObj;
    std::map<int, int> materialByNode;
    std::map<int, int> colorByNode;
    std::map<int, std::vector<int>> instancesByObj;
    std::map<int, std::vector<int>> childInstancesByDef;
    std::map<int, int> containerByObj;
    std::map<int, int> placementByObj;
    {
        // The SQL this replaces: WHERE rel IN (…) ORDER BY src, ord — collect the
        // filtered rows, sort by (src, ord), then bucket per rel so each per-src
        // vector keeps its ord order.
        struct RelRow
        {
            int rel, src, dst, ord;
        };
        std::vector<RelRow> relRows;

        ParquetFile f(relationsPath, { "rel", "src", "dst", "ord" });
        minipq::Batch batch;
        while (f.Next(batch, relationsPath))
        {
            const auto rel = minipq::i32(batch, f.cols[0]);
            const auto src = minipq::i32(batch, f.cols[1]);
            const auto dst = minipq::i32(batch, f.cols[2]);
            const auto ord = minipq::i32(batch, f.cols[3]);
            for (std::int64_t r = 0; r < batch.num_rows(); r++)
            {
                const int relValue = rel.Value(r);
                switch (relValue)
                {
                case 1: case 2: case 4: case 5: case 6: case 8: case 9:
                case 10: case 24: case 26: case 27: case 28: case 29:
                    break;
                default:
                    continue;
                }
                // NULL ord sorts last, matching DuckDB's default NULLS LAST.
                const int ordValue = ord.IsNull(r) ? std::numeric_limits<int>::max() : ord.Value(r);
                relRows.push_back({ relValue, src.Value(r), dst.Value(r), ordValue });
            }
        }
        std::stable_sort(relRows.begin(), relRows.end(), [](const RelRow& a, const RelRow& b)
        {
            return a.src != b.src ? a.src < b.src : a.ord < b.ord;
        });

        for (const RelRow& row : relRows)
        {
            // Appearance edges are single-valued per src (last write wins, matching the
            // deployed receives); geometry/placement edges are ordered lists.
            switch (row.rel)
            {
            case 1: displayByObj[row.src].push_back(row.dst); break;
            case 2: solidByObj[row.src].push_back(row.dst); break;
            case 4: definesByDef[row.src].push_back(row.dst); break;
            case 5: materialByGeom[row.src] = row.dst; break;
            case 6: colorByGeom[row.src] = row.dst; break;
            case 8: instancesByObj[row.src].push_back(row.dst); break;
            case 9: childInstancesByDef[row.src].push_back(row.dst); break;
            case 10: containerByObj[row.src] = row.dst; break;
            case 24: placementByObj[row.src] = row.dst; break;
            case 26: materialByObj[row.src] = row.dst; break;
            case 27: colorByObj[row.src] = row.dst; break;
            case 28: materialByNode[row.src] = row.dst; break;
            case 29: colorByNode[row.src] = row.dst; break;
            default: break;
            }
        }
    }

    struct InstanceNode
    {
        int defRef = -1;
        Mat4 transform;
    };
    struct MaterialNode
    {
        std::string name;
        int argb = 0;
        double opacity = 1.0;
        double roughness = 1.0;
        int emissive = 0; // packed ARGB; 0 = no emission (spec writes NULL for it)
    };
    std::map<int, InstanceNode> instanceNodes;
    std::map<int, MaterialNode> materialNodes;
    {
        ParquetFile f(
            nodesPath,
            { "id", "kind", "name", "def_ref", "transform", "units", "argb", "opacity", "roughness" },
            { "emissive" });
        minipq::Batch batch;
        while (f.Next(batch, nodesPath))
        {
            const auto idCol = minipq::i32(batch, f.cols[0]);
            const auto kindCol = minipq::i32(batch, f.cols[1]);
            const auto nameCol = minipq::bytes(batch, f.cols[2]);
            const auto defRefCol = minipq::i32(batch, f.cols[3]);
            const auto transformCol = minipq::bytes(batch, f.cols[4]);
            const auto unitsCol = minipq::bytes(batch, f.cols[5]);
            const auto argbCol = minipq::i32(batch, f.cols[6]);
            const auto opacityCol = minipq::f64(batch, f.cols[7]);
            const auto roughnessCol = minipq::f64(batch, f.cols[8]);
            std::optional<minipq::Int32Arr> emissiveCol;
            if (f.optCols[0] >= 0)
                emissiveCol = minipq::i32(batch, f.optCols[0]);
            for (std::int64_t r = 0; r < batch.num_rows(); r++)
            {
                const int kind = kindCol.Value(r); // INSTANCE=2, MATERIAL=3
                if (kind != 2 && kind != 3)
                    continue;
                const int id = idCol.Value(r);
                if (kind == 2)
                {
                    InstanceNode node;
                    if (!defRefCol.IsNull(r))
                        node.defRef = defRefCol.Value(r);
                    const std::string transform = StrOrEmpty(transformCol, r);
                    const std::string units = StrOrEmpty(unitsCol, r);
                    if (!transform.empty())
                        ParseTransform(transform, units, node.transform);
                    instanceNodes[id] = node;
                }
                else
                {
                    MaterialNode node;
                    node.name = StrOrEmpty(nameCol, r);
                    if (!argbCol.IsNull(r))
                        node.argb = argbCol.Value(r);
                    if (!opacityCol.IsNull(r))
                        node.opacity = opacityCol.Value(r);
                    if (!roughnessCol.IsNull(r))
                        node.roughness = roughnessCol.Value(r);
                    if (emissiveCol && !emissiveCol->IsNull(r))
                        node.emissive = emissiveCol->Value(r);
                    materialNodes[id] = node;
                }
            }
        }
    }

    std::map<int, std::pair<std::vector<std::uint8_t>, std::string>> geometryBlobs;
    for (const auto& geometryPath : geometryPaths) // multi-file union, one file at a time
    {
        ParquetFile f(geometryPath, { "geometryIndex", "content", "type" });
        minipq::Batch batch;
        while (f.Next(batch, geometryPath))
        {
            const auto geometryIndex = minipq::i32(batch, f.cols[0]);
            const auto content = minipq::bytes(batch, f.cols[1]);
            const auto type = minipq::bytes(batch, f.cols[2]);
            for (std::int64_t r = 0; r < batch.num_rows(); r++)
            {
                const int k = geometryIndex.Value(r);
                std::vector<std::uint8_t> blob;
                if (!content.IsNull(r))
                {
                    const std::string_view v = content.GetView(r);
                    blob.assign(
                        reinterpret_cast<const std::uint8_t*>(v.data()),
                        reinterpret_cast<const std::uint8_t*>(v.data()) + v.size());
                }
                geometryBlobs[k] = { std::move(blob), StrOrEmpty(type, r) };
            }
        }
    }

    // ── 3. assemble per-object meshes and write XMLs ─────────────────────────
    // Objects with a DISPLAY or DISPLAY_INSTANCE edge are bakeable; everything
    // else (levels-only rows, data-only objects) is silently skipped — same
    // scope as the old desktop-service path (geometry + materials only).
    std::set<int> bakeableObjects;
    for (const auto& kv : displayByObj)
        bakeableObjects.insert(kv.first);
    for (const auto& kv : instancesByObj)
        bakeableObjects.insert(kv.first);
    // SOLID-only objects are candidates too — see the solid fallback below. An object
    // with both edges is already here via DISPLAY.
    for (const auto& kv : solidByObj)
        bakeableObjects.insert(kv.first);

    processWindow.SetNextProcessPhase("Generating objects", static_cast<int>(bakeableObjects.size()));

    constexpr double LIGHT_GRAY = 211.0 / 255.0;
    const std::string defaultMaterialName = "specke_default_material"; // (sic) — matches the C# service

    // Batch layout, matching FileConverter: 1 folder below 100 objects, else 8.
    const int objectTotal = static_cast<int>(bakeableObjects.size());
    const int parallelConversions = objectTotal >= 100 ? 8 : 1;
    const int maxFilesPerFolder =
        objectTotal >= 100 ? static_cast<int>(std::ceil(objectTotal / 8.0)) : 100;

    std::vector<std::string> batchFolders;
    auto ensureBatchFolder = [&](int index) -> const std::string&
    {
        while (static_cast<int>(batchFolders.size()) <= index)
        {
            char name[32];
            std::snprintf(name, sizeof(name), "Batch_%03d", static_cast<int>(batchFolders.size()) + 1);
            const fs::path p = rootDir / name;
            fs::create_directories(p);
            batchFolders.push_back(p.string());
        }
        return batchFolders[index];
    };

    // Recursively expand an INSTANCE node into (geometryK, worldTransform) pairs.
    struct MeshInstance
    {
        int geometryK;
        Mat4 transform;
        bool hasTransform;
    };
    std::function<void(int, const Mat4&, bool, int, std::vector<MeshInstance>&)> expandInstance =
        [&](int instK, const Mat4& parent, bool parentHasTransform, int depth, std::vector<MeshInstance>& out)
    {
        if (depth > 64)
            return; // nesting backstop
        auto it = instanceNodes.find(instK);
        if (it == instanceNodes.end() || it->second.defRef < 0)
            return;
        const InstanceNode& inst = it->second;

        Mat4 combined = inst.transform;
        bool hasTransform = !inst.transform.isIdentity;
        if (parentHasTransform)
        {
            combined = hasTransform ? Mat4::Multiply(parent, inst.transform) : parent;
            hasTransform = true;
        }

        auto geoms = definesByDef.find(inst.defRef);
        if (geoms != definesByDef.end())
        {
            for (const int geomK : geoms->second)
                out.push_back({ geomK, combined, hasTransform });
        }
        auto children = childInstancesByDef.find(inst.defRef);
        if (children != childInstancesByDef.end())
        {
            for (const int childK : children->second)
                expandInstance(childK, combined, hasTransform, depth + 1, out);
        }
    };

    int written = 0;
    int progress = 0;
    for (const int objK : bakeableObjects)
    {
        progress++;
        processWindow.SetProcessValue(progress);
        if (processWindow.IsProcessCanceled())
            throw UserCancelledException("The user cancelled the receive operation");

        const std::string applicationId =
            appIdByObj.count(objK) ? appIdByObj[objK] : ("object_" + std::to_string(objK));

        ReceiveConversionResult conversionResult;
        conversionResult.sourceId = applicationId;
        conversionResult.sourceType = "DataObject";

        try
        {
            std::vector<MeshInstance> meshInstances;
            auto direct = displayByObj.find(objK);
            if (direct != displayByObj.end())
            {
                for (const int geomK : direct->second)
                    meshInstances.push_back({ geomK, Mat4{}, false });
            }
            // SOLID (2) is a FALLBACK here, never a preference — the deliberate inverse of
            // the spec's "receive prefers the solid over its meshes", which presumes a
            // consumer that can read the raw encoding. A SOLID blob is raw, non-SGEO
            // content (a Rhino Brep/Extrusion/SubD stored verbatim, geometries.type "3dm");
            // the SDK gates it on ArtifactReceiveOptions.PreferSolids, true for Rhino and
            // false for Revit "which can't import 3dm". Archicad can't either — it bakes
            // GDL from decoded triangles — so preferring the solid would decode nothing and
            // silently drop the object's geometry. We take the display meshes, and consult
            // the solid only when there are none, for the case where a producer happened to
            // mesh-encode it (TryDecodeMesh rejects the raw blobs below either way).
            if (meshInstances.empty())
            {
                auto solids = solidByObj.find(objK);
                if (solids != solidByObj.end())
                {
                    for (const int geomK : solids->second)
                        meshInstances.push_back({ geomK, Mat4{}, false });
                }
            }
            auto placed = instancesByObj.find(objK);
            if (placed != instancesByObj.end())
            {
                for (const int instK : placed->second)
                    expandInstance(instK, Mat4{}, false, 0, meshInstances);
            }

            std::vector<GdlLibpartXml::XmlMesh> xmlMeshes;
            std::map<int, GdlLibpartXml::XmlMaterial> usedMaterials; // matK -> def
            bool usedDefaultMaterial = false;

            for (const auto& mi : meshInstances)
            {
                auto blob = geometryBlobs.find(mi.geometryK);
                if (blob == geometryBlobs.end())
                    continue;

                SgeoDecoder::DecodedMesh decoded;
                try
                {
                    if (!SgeoDecoder::TryDecodeMesh(blob->second.first.data(), blob->second.first.size(), decoded))
                        continue; // non-mesh primitive (lines/points) or raw solid — geometry-only scope
                }
                catch (const std::exception&)
                {
                    continue; // corrupt blob — skip the fragment, keep the object
                }

                const double factor = UnitsToMetersFactor(decoded.units);
                if (factor != 1.0)
                {
                    for (auto& v : decoded.vertices)
                        v *= factor;
                }
                if (mi.hasTransform)
                {
                    for (size_t i = 0; i + 2 < decoded.vertices.size(); i += 3)
                        mi.transform.TransformPoint(decoded.vertices[i], decoded.vertices[i + 1], decoded.vertices[i + 2]);
                }

                // Material: HAS_MATERIAL geometry → MATERIAL node; default light gray.
                std::string materialName = defaultMaterialName;
                auto matRel = materialByGeom.find(mi.geometryK);
                if (matRel != materialByGeom.end())
                {
                    auto mat = materialNodes.find(matRel->second);
                    if (mat != materialNodes.end())
                    {
                        auto& def = usedMaterials[matRel->second];
                        if (def.name.empty())
                        {
                            std::string rawName = mat->second.name.empty()
                                ? ("Speckle Material " + std::to_string(matRel->second))
                                : mat->second.name;
                            def.name = GdlLibpartXml::SanitizeName(rawName);
                            const int argb = mat->second.argb;
                            def.r = ((argb >> 16) & 0xFF) / 255.0;
                            def.g = ((argb >> 8) & 0xFF) / 255.0;
                            def.b = (argb & 0xFF) / 255.0;
                            def.transparent = 1.0 - mat->second.opacity;
                            def.shining = static_cast<int>((1.0 - mat->second.roughness) * 100);
                            const int emissive = mat->second.emissive;
                            if (emissive != 0)
                            {
                                def.hasEmission = true;
                                def.emissionR = ((emissive >> 16) & 0xFF) / 255.0;
                                def.emissionG = ((emissive >> 8) & 0xFF) / 255.0;
                                def.emissionB = (emissive & 0xFF) / 255.0;
                            }
                        }
                        materialName = def.name;
                    }
                }
                if (materialName == defaultMaterialName)
                    usedDefaultMaterial = true;

                GdlLibpartXml::XmlMesh xmlMesh;
                xmlMesh.vertices = std::move(decoded.vertices);
                xmlMesh.faces = std::move(decoded.faces);
                xmlMesh.materialName = materialName;
                xmlMeshes.push_back(std::move(xmlMesh));
            }

            if (xmlMeshes.empty())
                continue; // nothing bakeable (data-only / unsupported geometry) — silent skip

            std::vector<GdlLibpartXml::XmlMaterial> materials;
            if (usedDefaultMaterial)
            {
                GdlLibpartXml::XmlMaterial def;
                def.name = defaultMaterialName;
                def.r = def.g = def.b = LIGHT_GRAY;
                materials.push_back(def);
            }
            for (const auto& kv : usedMaterials)
                materials.push_back(kv.second);

            const std::string xml = GdlLibpartXml::BuildSymbolXml(materials, xmlMeshes);
            const std::string& folder = ensureBatchFolder(written / maxFilesPerFolder);
            const fs::path xmlPath = fs::path(folder) / ("speckle_object_" + std::to_string(written + 1) + ".xml");
            std::ofstream out(xmlPath, std::ios::binary);
            if (!out)
                throw std::runtime_error("Could not write " + xmlPath.string());
            out << xml;
            out.close();
            written++;

            conversionResult.status = ConversionResultStatus::CONVERSION_SUCCESS;
            result.conversionResults.push_back(conversionResult);
        }
        catch (const UserCancelledException&)
        {
            throw;
        }
        catch (const std::exception& ex)
        {
            conversionResult.status = ConversionResultStatus::CONVERSION_ERROR;
            conversionResult.error.message = ex.what();
            result.conversionResults.push_back(conversionResult);
        }
    }

    result.objectCount = written;
    if (written == 0)
        throw std::runtime_error("The received version contains no bakeable geometry");

    // ── 4. XML → GSM via LP_XMLConverter, one process per batch folder ──────
    processWindow.SetNextProcessPhase("Converting to GSM", static_cast<int>(batchFolders.size()));
    (void)parallelConversions; // folder count is already <= 8 by construction

    std::vector<ConverterProcess> processes;
    processes.reserve(batchFolders.size());
    for (const auto& folder : batchFolders)
        processes.push_back(StartConverter(xmlConverterPath, folder, outputDir.string()));

    int finished = 0;
    while (finished < static_cast<int>(processes.size()))
    {
        std::vector<HANDLE> pending;
        for (const auto& p : processes)
        {
            if (p.process != nullptr)
                pending.push_back(p.process);
        }
        if (pending.empty())
            break; // defensive: bookkeeping says done
        const DWORD waited = WaitForMultipleObjects(
            static_cast<DWORD>(pending.size()), pending.data(), FALSE, 500);
        if (waited >= WAIT_OBJECT_0 && waited < WAIT_OBJECT_0 + pending.size())
        {
            HANDLE done = pending[waited - WAIT_OBJECT_0];
            for (auto& p : processes)
            {
                if (p.process == done)
                {
                    CloseHandle(p.process);
                    p.process = nullptr;
                    finished++;
                    processWindow.SetProcessValue(finished);
                }
            }
        }
        if (processWindow.IsProcessCanceled())
        {
            for (auto& p : processes)
            {
                if (p.process != nullptr)
                {
                    TerminateProcess(p.process, 1);
                    CloseHandle(p.process);
                    p.process = nullptr;
                }
            }
            throw UserCancelledException("The user cancelled the receive operation");
        }
    }

    // Sanity: the converter reports success only through its output.
    bool anyGsm = false;
    for (const auto& entry : fs::directory_iterator(outputDir))
    {
        if (entry.is_regular_file())
        {
            anyGsm = true;
            break;
        }
    }
    if (!anyGsm)
        throw std::runtime_error("LP_XMLConverter produced no GSM files (check " + result.rootDir + ")");

    return result;
#endif
}
