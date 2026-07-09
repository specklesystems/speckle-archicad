#include "BundleWriter.h"

#include <cctype>
#include <charconv>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <stdexcept>

#include "duckdb.h"
#include "picosha2.h"
#include "DuckDbRuntime.h"

namespace
{
    constexpr int MAX_DEPTH = 10;

    duckdb_appender Appender(void* p) { return static_cast<duckdb_appender>(p); }

    std::string FormatDouble(double d)
    {
        char buf[64];
        auto res = std::to_chars(buf, buf + sizeof(buf), d);
        return std::string(buf, res.ptr);
    }

    // Port of EavExtraction's UUID-like rejection regex ".-.-":
    // any char, '-', any char, '-' anywhere in the string.
    bool LooksUuidLike(const std::string& s)
    {
        if (s.size() < 4)
            return false;
        for (size_t i = 0; i + 3 < s.size(); i++)
        {
            if (s[i + 1] == '-' && s[i + 3] == '-')
                return true;
        }
        return false;
    }

    std::string Trim(const std::string& s)
    {
        size_t start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos)
            return "";
        size_t end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    bool TryParseDouble(const std::string& s, double& out)
    {
        const std::string trimmed = Trim(s);
        if (trimmed.empty())
            return false;
        char* end = nullptr;
        out = std::strtod(trimmed.c_str(), &end);
        if (end != trimmed.c_str() + trimmed.size())
            return false;
        return std::isfinite(out);
    }

    // "boolean" | "number" | "string" — ports EavExtraction.InferTypeNative.
    std::string InferType(const nlohmann::json& v)
    {
        if (v.is_boolean())
            return "boolean";
        if (v.is_number_float())
            return std::isfinite(v.get<double>()) ? "number" : "string";
        if (v.is_number())
            return "number";
        if (v.is_string())
        {
            std::string s = v.get<std::string>();
            std::string lower = s;
            for (auto& c : lower)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (lower == "true" || lower == "false")
                return "boolean";
            const std::string trimmed = Trim(s);
            if (trimmed.empty() || LooksUuidLike(trimmed))
                return "string";
            double d;
            return TryParseDouble(trimmed, d) ? "number" : "string";
        }
        return "string";
    }

    // JS String(value) semantics — ports EavExtraction.ToTextNative.
    std::string ToText(const nlohmann::json& v)
    {
        if (v.is_boolean())
            return v.get<bool>() ? "true" : "false";
        if (v.is_string())
            return v.get<std::string>();
        if (v.is_number_float())
            return FormatDouble(v.get<double>());
        if (v.is_number_integer())
            return std::to_string(v.get<long long>());
        if (v.is_number_unsigned())
            return std::to_string(v.get<unsigned long long>());
        return v.dump();
    }

    bool IsScalar(const nlohmann::json& v)
    {
        return v.is_boolean() || v.is_string() || v.is_number();
    }

    // Joins an array's scalar elements into one comma-separated string, reusing the
    // same String(value) text as scalar rows. Null / non-scalar elements are skipped
    // (Archicad property arrays are always scalar-valued in practice). Returns "" for
    // an empty or all-non-scalar array so the caller can drop it instead of emitting a
    // blank row.
    std::string JoinArrayScalars(const nlohmann::json& arr)
    {
        std::string out;
        bool first = true;
        for (const auto& el : arr)
        {
            if (el.is_null() || !IsScalar(el))
                continue;
            if (!first)
                out += ", ";
            out += ToText(el);
            first = false;
        }
        return out;
    }

    std::string EscapeSqlLiteral(const std::string& s)
    {
        std::string out;
        out.reserve(s.size());
        for (char c : s)
        {
            out.push_back(c);
            if (c == '\'')
                out.push_back('\'');
        }
        return out;
    }
}

BundleWriter::BundleWriter(const std::string& outputDir, const std::string& baseName)
    : _outputDir(outputDir), _baseName(baseName)
{
    DuckDbRuntime::EnsureLoaded();
    std::filesystem::create_directories(outputDir);

    duckdb_database db = nullptr;
    duckdb_connection con = nullptr;
    if (duckdb_open(nullptr, &db) != DuckDBSuccess)
        throw std::runtime_error("BundleWriter: failed to open in-memory DuckDB");
    _db = db;
    if (duckdb_connect(db, &con) != DuckDBSuccess)
        throw std::runtime_error("BundleWriter: failed to connect to DuckDB");
    _con = con;

    // Table shapes follow speckle-bundle-spec (schema_version 5); the vocab/catalog
    // tables mirror what the SDK's EnvelopeWriter actually writes into a bundle.
    Execute("CREATE TABLE objects (object_index INTEGER NOT NULL, application_id VARCHAR NOT NULL)");
    Execute("CREATE TABLE paths (path_index INTEGER NOT NULL, path VARCHAR NOT NULL)");
    Execute(
        "CREATE TABLE eav (object_index INTEGER, path_index INTEGER, value_string VARCHAR, "
        "value_double DOUBLE, value_boolean BOOLEAN, unit VARCHAR, internal_definition_name VARCHAR)");
    Execute(
        "CREATE TABLE nodes (id INTEGER NOT NULL, kind INTEGER NOT NULL, name VARCHAR, def_ref INTEGER, "
        "transform VARCHAR, units VARCHAR, subtype VARCHAR, argb INTEGER, opacity DOUBLE, "
        "metalness DOUBLE, roughness DOUBLE, elevation DOUBLE)");
    Execute("CREATE TABLE relations (rel INTEGER NOT NULL, src INTEGER NOT NULL, dst INTEGER NOT NULL, ord INTEGER)");
    Execute("CREATE TABLE scene_views (view INTEGER NOT NULL, name VARCHAR, is_default BOOLEAN, ord INTEGER, source VARCHAR, ref VARCHAR)");
    Execute("CREATE TABLE geometries (geometryIndex INTEGER NOT NULL, content BLOB, id VARCHAR, type VARCHAR)");
    Execute("CREATE TABLE meta (schema_version INTEGER, produced_by VARCHAR)");
    Execute("CREATE TABLE rel_types (rel INTEGER, name VARCHAR, src_ns VARCHAR, dst_ns VARCHAR)");
    Execute("CREATE TABLE node_kinds (kind INTEGER, name VARCHAR)");
    // Type-dedup tables (spec: optional; viewer: REQUIRED). Archicad has no type
    // parameter dedup yet, so they stay empty — but the viewer's loader only creates
    // its object_properties view (which every scene-tree/property query reads) when
    // eav + object_type + type_eav are ALL present, so they must ship regardless.
    Execute("CREATE TABLE types (type_index INTEGER NOT NULL, type_key VARCHAR NOT NULL)");
    Execute(
        "CREATE TABLE type_eav (type_index INTEGER, path_index INTEGER, value_string VARCHAR, "
        "value_double DOUBLE, value_boolean BOOLEAN, unit VARCHAR, internal_definition_name VARCHAR)");
    Execute("CREATE TABLE object_type (object_index INTEGER NOT NULL, type_index INTEGER NOT NULL)");

    for (const char* table : { "objects", "paths", "eav", "nodes", "relations", "scene_views", "geometries" })
    {
        duckdb_appender appender = nullptr;
        if (duckdb_appender_create(con, nullptr, table, &appender) != DuckDBSuccess)
            throw std::runtime_error(std::string("BundleWriter: failed to create appender for ") + table);
        _appenders[table] = appender;
    }

    WriteVocabTables();
}

BundleWriter::~BundleWriter()
{
    for (auto& kv : _appenders)
    {
        auto appender = Appender(kv.second);
        duckdb_appender_destroy(&appender);
    }
    _appenders.clear();
    if (_con)
    {
        auto con = static_cast<duckdb_connection>(_con);
        duckdb_disconnect(&con);
        _con = nullptr;
    }
    if (_db)
    {
        auto db = static_cast<duckdb_database>(_db);
        duckdb_close(&db);
        _db = nullptr;
    }
}

void BundleWriter::Execute(const std::string& sql)
{
    duckdb_result result;
    if (duckdb_query(static_cast<duckdb_connection>(_con), sql.c_str(), &result) != DuckDBSuccess)
    {
        std::string error = duckdb_result_error(&result) ? duckdb_result_error(&result) : "unknown DuckDB error";
        duckdb_destroy_result(&result);
        throw std::runtime_error("BundleWriter SQL failed: " + error);
    }
    duckdb_destroy_result(&result);
}

void BundleWriter::WriteVocabTables()
{
    // meta + rel/kind vocab, from the vendored generated spec (Libs/bundlespec).
    Execute("INSERT INTO meta VALUES (" + std::to_string(bundlespec::kSchemaVersion) + ", 'Speckle Archicad BundleWriter')");
    for (const auto& r : bundlespec::kRelTypes)
    {
        Execute(
            "INSERT INTO rel_types VALUES (" + std::to_string(r.id) + ", '" + EscapeSqlLiteral(r.name) + "', " +
            (r.src_ns ? "'" + EscapeSqlLiteral(r.src_ns) + "'" : "NULL") + ", " +
            (r.dst_ns ? "'" + EscapeSqlLiteral(r.dst_ns) + "'" : "NULL") + ")");
    }
    for (const auto& k : bundlespec::kNodeKinds)
    {
        Execute("INSERT INTO node_kinds VALUES (" + std::to_string(k.id) + ", '" + EscapeSqlLiteral(k.name) + "')");
    }
}

int BundleWriter::InternObject(const std::string& applicationId)
{
    auto it = _objectIndex.find(applicationId);
    if (it != _objectIndex.end())
        return it->second;

    const int k = static_cast<int>(_objectIndex.size());
    _objectIndex.emplace(applicationId, k);

    auto appender = Appender(_appenders["objects"]);
    duckdb_append_int32(appender, k);
    duckdb_append_varchar(appender, applicationId.c_str());
    duckdb_appender_end_row(appender);
    return k;
}

void BundleWriter::AddEavRow(
    int objectK,
    const std::string& path,
    const nlohmann::json& value,
    const std::string* units,
    const std::string* internalDefinitionName)
{
    int pathK;
    auto it = _pathIndex.find(path);
    if (it != _pathIndex.end())
    {
        pathK = it->second;
    }
    else
    {
        pathK = static_cast<int>(_pathIndex.size());
        _pathIndex.emplace(path, pathK);
        auto pathsAppender = Appender(_appenders["paths"]);
        duckdb_append_int32(pathsAppender, pathK);
        duckdb_append_varchar(pathsAppender, path.c_str());
        duckdb_appender_end_row(pathsAppender);
    }

    const std::string type = InferType(value);
    const std::string text = ToText(value);

    auto appender = Appender(_appenders["eav"]);
    duckdb_append_int32(appender, objectK);
    duckdb_append_int32(appender, pathK);
    duckdb_append_varchar(appender, text.c_str());

    if (type == "number")
    {
        double num = 0;
        bool ok = false;
        if (value.is_number())
        {
            num = value.get<double>();
            ok = std::isfinite(num);
        }
        else if (value.is_string())
        {
            ok = TryParseDouble(value.get<std::string>(), num);
        }
        if (ok)
            duckdb_append_double(appender, num);
        else
            duckdb_append_null(appender);
    }
    else
    {
        duckdb_append_null(appender);
    }

    if (type == "boolean")
    {
        // Case-insensitive, matching the SDK's bool.TryParse semantics — Archicad
        // extractors historically emitted "True"/"False" with a capital.
        std::string lower = text;
        for (auto& c : lower)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        duckdb_append_bool(appender, lower == "true");
    }
    else
        duckdb_append_null(appender);

    if (units)
        duckdb_append_varchar(appender, units->c_str());
    else
        duckdb_append_null(appender);

    if (internalDefinitionName)
        duckdb_append_varchar(appender, internalDefinitionName->c_str());
    else
        duckdb_append_null(appender);

    duckdb_appender_end_row(appender);
}

void BundleWriter::WalkProperties(int objectK, const nlohmann::json& obj, const std::string& prefix, int depth)
{
    if (depth >= MAX_DEPTH || !obj.is_object())
        return;

    for (auto it = obj.begin(); it != obj.end(); ++it)
    {
        const std::string& key = it.key();
        const nlohmann::json& val = it.value();
        if (val.is_null())
            continue;

        const std::string path = prefix + "." + key;

        if (val.is_object())
        {
            // Parameter pattern { name, value } -> a single row at this path.
            if (val.contains("name") && val.contains("value"))
            {
                const nlohmann::json& paramVal = val["value"];
                if (!IsScalar(paramVal))
                    continue;
                std::string unitsStorage, idnStorage;
                const std::string* units = nullptr;
                const std::string* idn = nullptr;
                if (val.contains("units") && val["units"].is_string())
                {
                    unitsStorage = val["units"].get<std::string>();
                    units = &unitsStorage;
                }
                if (val.contains("internalDefinitionName") && val["internalDefinitionName"].is_string())
                {
                    idnStorage = val["internalDefinitionName"].get<std::string>();
                    idn = &idnStorage;
                }
                AddEavRow(objectK, path, paramVal, units, idn);
                continue;
            }
            WalkProperties(objectK, val, path, depth + 1);
            continue;
        }

        if (IsScalar(val))
        {
            AddEavRow(objectK, path, val, nullptr, nullptr);
            continue;
        }

        if (val.is_array())
        {
            // Archicad — unlike Revit, which the SDK's array-skipping walk was shaped
            // around — emits genuinely multi-valued properties as JSON arrays (native
            // List / Multiple-Choice Enumeration collection types, and IFC List /
            // Enumerated properties). The EAV model is one value per row, so we collapse
            // the elements into a single comma-separated string to preserve them rather
            // than drop the whole property. (IFC bounded ranges are split into lower/upper
            // rows upstream, so they never reach here as an array.)
            const std::string joined = JoinArrayScalars(val);
            if (!joined.empty())
                AddEavRow(objectK, path, nlohmann::json(joined), nullptr, nullptr);
            continue;
        }
        // remaining non-scalars (nested arrays, objects without name/value) are skipped
    }
}

void BundleWriter::AddProperties(
    const std::string& applicationId,
    const nlohmann::json& properties,
    const std::vector<std::pair<std::string, nlohmann::json>>& rootScalars)
{
    const int objectK = InternObject(applicationId);

    for (const auto& kv : rootScalars)
    {
        if (IsScalar(kv.second))
            AddEavRow(objectK, kv.first, kv.second, nullptr, nullptr);
    }

    if (properties.is_object() && !properties.empty())
        WalkProperties(objectK, properties, "properties", 0);
}

int BundleWriter::AddGeometrySgeo(
    const std::string& geometryApplicationId,
    const std::vector<std::uint8_t>& sgeoBlob,
    const std::string& typeName)
{
    auto it = _geometryIndex.find(geometryApplicationId);
    if (it != _geometryIndex.end())
        return it->second;

    const int k = static_cast<int>(_geometryIndex.size());
    _geometryIndex.emplace(geometryApplicationId, k);

    // id = SHA256 hex of the content (read-time shape dedup), matching GeometriesParquetWriter.
    const std::string id = picosha2::hash256_hex_string(sgeoBlob.begin(), sgeoBlob.end());

    auto appender = Appender(_appenders["geometries"]);
    duckdb_append_int32(appender, k);
    duckdb_append_blob(appender, sgeoBlob.data(), static_cast<idx_t>(sgeoBlob.size()));
    duckdb_append_varchar(appender, id.c_str());
    duckdb_append_varchar(appender, typeName.c_str());
    duckdb_appender_end_row(appender);
    return k;
}

int BundleWriter::InternNode(const std::string& key, bool& isNew)
{
    auto it = _nodeIndex.find(key);
    if (it != _nodeIndex.end())
    {
        isNew = false;
        return it->second;
    }
    const int k = static_cast<int>(_nodeIndex.size());
    _nodeIndex.emplace(key, k);
    isNew = true;
    return k;
}

// Appends one row to nodes with only the kind-relevant columns set.
// Column order: id, kind, name, def_ref, transform, units, subtype, argb, opacity, metalness, roughness, elevation
static void AppendNodeRow(
    duckdb_appender appender,
    int id,
    int kind,
    const std::string* name,
    const int* defRef,
    const std::string* transform,
    const std::string* units,
    const std::string* subtype,
    const int* argb,
    const double* opacity,
    const double* metalness,
    const double* roughness,
    const double* elevation)
{
    duckdb_append_int32(appender, id);
    duckdb_append_int32(appender, kind);
    if (name) duckdb_append_varchar(appender, name->c_str()); else duckdb_append_null(appender);
    if (defRef) duckdb_append_int32(appender, *defRef); else duckdb_append_null(appender);
    if (transform) duckdb_append_varchar(appender, transform->c_str()); else duckdb_append_null(appender);
    if (units) duckdb_append_varchar(appender, units->c_str()); else duckdb_append_null(appender);
    if (subtype) duckdb_append_varchar(appender, subtype->c_str()); else duckdb_append_null(appender);
    if (argb) duckdb_append_int32(appender, *argb); else duckdb_append_null(appender);
    if (opacity) duckdb_append_double(appender, *opacity); else duckdb_append_null(appender);
    if (metalness) duckdb_append_double(appender, *metalness); else duckdb_append_null(appender);
    if (roughness) duckdb_append_double(appender, *roughness); else duckdb_append_null(appender);
    if (elevation) duckdb_append_double(appender, *elevation); else duckdb_append_null(appender);
    duckdb_appender_end_row(appender);
}

int BundleWriter::AddMaterial(const std::string& materialKey, int argb, double opacity, double metalness, double roughness)
{
    bool isNew;
    const int k = InternNode("mat:" + materialKey, isNew);
    if (isNew)
    {
        AppendNodeRow(
            Appender(_appenders["nodes"]), k, static_cast<int>(bundlespec::NodeKind::MATERIAL),
            nullptr, nullptr, nullptr, nullptr, nullptr, &argb, &opacity, &metalness, &roughness, nullptr);
    }
    return k;
}

int BundleWriter::AddLevel(const std::string& levelKey, const std::string& name, double elevation)
{
    bool isNew;
    const int k = InternNode("lvl:" + levelKey, isNew);
    if (isNew)
    {
        AppendNodeRow(
            Appender(_appenders["nodes"]), k, static_cast<int>(bundlespec::NodeKind::LEVEL),
            &name, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &elevation);
    }
    return k;
}

int BundleWriter::AddCollection(const std::string& collectionKey, const std::string& name, const int* parentK, const std::string& subtype)
{
    bool isNew;
    const int k = InternNode("coll:" + collectionKey, isNew);
    if (isNew)
    {
        AppendNodeRow(
            Appender(_appenders["nodes"]), k, static_cast<int>(bundlespec::NodeKind::CONTAINER),
            &name, parentK, nullptr, nullptr, &subtype, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    return k;
}

int BundleWriter::AddContainer(const std::string& containerKey, const std::string& name, const int* parentK, const std::string& subtype)
{
    bool isNew;
    const int k = InternNode("cont:" + containerKey, isNew);
    if (isNew)
    {
        AppendNodeRow(
            Appender(_appenders["nodes"]), k, static_cast<int>(bundlespec::NodeKind::CONTAINER),
            &name, parentK, nullptr, nullptr, &subtype, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    return k;
}

void BundleWriter::AddRelation(bundlespec::Rel rel, int src, int dst, int ord)
{
    auto appender = Appender(_appenders["relations"]);
    duckdb_append_int32(appender, static_cast<int>(rel));
    duckdb_append_int32(appender, src);
    duckdb_append_int32(appender, dst);
    duckdb_append_int32(appender, ord);
    duckdb_appender_end_row(appender);
}

void BundleWriter::Display(int objectK, int geometryK, int ord) { AddRelation(bundlespec::Rel::DISPLAY, objectK, geometryK, ord); }
void BundleWriter::Subelement(int parentObjectK, int childObjectK, int ord) { AddRelation(bundlespec::Rel::SUBELEMENT, parentObjectK, childObjectK, ord); }
void BundleWriter::HasMaterial(int geometryK, int materialK) { AddRelation(bundlespec::Rel::HAS_MATERIAL, geometryK, materialK, 0); }
void BundleWriter::HasColor(int srcK, int colorK) { AddRelation(bundlespec::Rel::HAS_COLOR, srcK, colorK, 0); }
void BundleWriter::OnLevel(int objectK, int levelK) { AddRelation(bundlespec::Rel::ON_LEVEL, objectK, levelK, 0); }
void BundleWriter::InCollection(int objectK, int collectionK, int ord) { AddRelation(bundlespec::Rel::IN_COLLECTION, objectK, collectionK, ord); }
void BundleWriter::InModel(int objectK, int modelK, int ord) { AddRelation(bundlespec::Rel::IN_MODEL, objectK, modelK, ord); }

void BundleWriter::AddSceneView(int view, const std::string& name, bool isDefault, const std::vector<SceneViewTier>& tiers)
{
    auto appender = Appender(_appenders["scene_views"]);
    for (size_t ord = 0; ord < tiers.size(); ord++)
    {
        duckdb_append_int32(appender, view);
        duckdb_append_varchar(appender, name.c_str());
        duckdb_append_bool(appender, isDefault);
        duckdb_append_int32(appender, static_cast<int>(ord));
        duckdb_append_varchar(appender, tiers[ord].source.c_str());
        duckdb_append_varchar(appender, tiers[ord].ref.c_str());
        duckdb_appender_end_row(appender);
    }
}

std::map<std::string, std::string> BundleWriter::Complete()
{
    if (_completed)
        throw std::runtime_error("BundleWriter::Complete called twice");
    _completed = true;

    for (auto& kv : _appenders)
    {
        auto appender = Appender(kv.second);
        duckdb_appender_close(appender);
        duckdb_appender_destroy(&appender);
    }
    _appenders.clear();

    // table -> artefact file suffix ({base}.<suffix>.parquet)
    const std::vector<std::pair<std::string, std::string>> tables = {
        { "geometries", "geometries" },
        { "objects", "eav.objects" },
        { "paths", "eav.paths" },
        { "eav", "eav.eav" },
        { "types", "eav.types" },
        { "type_eav", "eav.type_eav" },
        { "object_type", "eav.object_type" },
        { "nodes", "envelope.nodes" },
        { "relations", "envelope.relations" },
        { "scene_views", "envelope.scene_views" },
        { "meta", "envelope.meta" },
        { "rel_types", "envelope.rel_types" },
        { "node_kinds", "envelope.node_kinds" },
    };

    std::map<std::string, std::string> files;
    for (const auto& t : tables)
    {
        const std::string fileName = _baseName + "." + t.second + ".parquet";
        std::filesystem::path fullPath = std::filesystem::path(_outputDir) / fileName;
        const std::string pathUtf8 = fullPath.string();
        // DICTIONARY_SIZE_LIMIT 0 disables dictionary encoding: the viewer's
        // duckdb-wasm build returned NULLs for our dictionary-encoded VARCHAR
        // columns (eav value_string), while the ecosystem-proven producers
        // (Parquet.Net, Arrow) emit PLAIN strings that read fine everywhere.
        Execute(
            "COPY " + t.first + " TO '" + EscapeSqlLiteral(pathUtf8) +
            "' (FORMAT PARQUET, COMPRESSION ZSTD, DICTIONARY_SIZE_LIMIT 0)");
        files[fileName] = pathUtf8;
    }
    return files;
}
