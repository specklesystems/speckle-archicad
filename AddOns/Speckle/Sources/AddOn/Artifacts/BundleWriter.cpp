#include "BundleWriter.h"

#include <cctype>
#include <charconv>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <optional>
#include <stdexcept>

#include "minipq.h"
#include "picosha2.h"
#include "Utf8Path.h"

// Named column indices generated from the spec (Libs/bundlespec). Using these
// instead of literal ordinals makes a spec column insertion a compile error
// rather than a silent row shift — the failure mode that once emptied nodes
// fleet-wide when emissive/ior were inserted ahead of elevation.
// bundle_cols.h declares camera_views::near/far, which windef.h defines as
// macros; undef them so this still compiles behind Archicad's headers.
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif
#include "bundle_cols.h"

namespace col = bundlespec::col;

namespace
{
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

    // nodes.transform is a CSV of 16 row-major doubles (M11..M44), invariant-culture
    // shortest round-trip — the exact format ObjectsArtifactReader.ParseTransform expects.
    std::string FormatTransform(const std::array<double, 16>& t)
    {
        std::string out;
        for (size_t i = 0; i < t.size(); i++)
        {
            if (i != 0)
                out.push_back(',');
            out += FormatDouble(t[i]);
        }
        return out;
    }

    // Column encoding policy — PR-15's minus dictionaries: int32 index columns are
    // dense/sequential (DELTA_BINARY_PACKED), everything else stays PLAIN until the
    // viewer is verified against dictionary-encoded bundles (the DuckDB writer shipped
    // PLAIN strings for the same reason: duckdb-wasm returned NULLs on its dict pages).
    minipq::Field I32(const char* name) { return { name, minipq::T::I32, minipq::Enc::DELTA_I32 }; }
    minipq::Field Str(const char* name) { return { name, minipq::T::UTF8, minipq::Enc::PLAIN }; }
    minipq::Field F64(const char* name) { return { name, minipq::T::F64, minipq::Enc::PLAIN }; }
    minipq::Field Bool(const char* name) { return { name, minipq::T::BOOL, minipq::Enc::PLAIN }; }
    minipq::Field Bin(const char* name) { return { name, minipq::T::BIN, minipq::Enc::PLAIN }; }

    // Nullable-column helpers (minipq needs an explicit put per column per row).
    void PutStrOpt(minipq::Table& t, int col, const std::string* v)
    {
        if (v)
            t.putStr(col, *v);
        else
            t.putStrNull(col);
    }
    void PutIntOpt(minipq::Table& t, int col, const int* v)
    {
        if (v)
            t.putInt(col, *v);
        else
            t.putIntNull(col);
    }
    std::optional<double> Opt(const double* v) { return v ? std::optional<double>(*v) : std::nullopt; }
}

// One minipq::Table per bundle file, each open at its final
// {baseName}.<group>.<table>.parquet path from construction on. Table shapes
// follow speckle-bundle-spec (schema_version 5); the vocab/catalog tables
// mirror what the SDK's EnvelopeWriter actually writes into a bundle.
struct BundleTables
{
    // Geometry blobs dominate bundle size — flush them by bytes so a large model
    // streams to disk in bounded row groups instead of sitting whole in RAM.
    static constexpr std::int64_t GEOMETRY_FLUSH_BYTES = 64ll << 20;

    minipq::Table objects;
    minipq::Table paths;
    minipq::Table eav;
    minipq::Table nodes;
    minipq::Table relations;
    minipq::Table sceneViews;
    minipq::Table geometries;
    minipq::Table meta;
    minipq::Table relTypes;
    minipq::Table nodeKinds;
    // Type-dedup tables (spec: optional; viewer: REQUIRED). Archicad has no type
    // parameter dedup yet, so they stay empty — but the viewer's loader only creates
    // its object_properties view (which every scene-tree/property query reads) when
    // eav + object_type + type_eav are ALL present, so they must ship regardless.
    minipq::Table types;
    minipq::Table typeEav;
    minipq::Table objectType;

    BundleTables(const std::filesystem::path& dir, const std::string& base)
        : objects(File(dir, base, "eav.objects"), { I32("object_index"), Str("application_id") })
        , paths(File(dir, base, "eav.paths"), { I32("path_index"), Str("path") })
        , eav(File(dir, base, "eav.eav"),
              { I32("object_index"), I32("path_index"), Str("value_string"), F64("value_double"),
                Bool("value_boolean"), Str("unit"), Str("internal_definition_name") })
        , nodes(File(dir, base, "envelope.nodes"),
                { I32("id"), I32("kind"), Str("name"), I32("def_ref"), Str("transform"), Str("units"),
                  Str("subtype"), I32("argb"), F64("opacity"), F64("metalness"), F64("roughness"),
                  I32("emissive"), F64("ior"), F64("elevation") })
        , relations(File(dir, base, "envelope.relations"), { I32("rel"), I32("src"), I32("dst"), I32("ord") })
        , sceneViews(File(dir, base, "envelope.scene_views"),
                     { I32("view"), Str("name"), Bool("is_default"), I32("ord"), Str("source"), Str("ref") })
        , geometries(File(dir, base, "geometries"),
                     { I32("geometryIndex"), Bin("content"), Str("id"), Str("type") },
                     200000, GEOMETRY_FLUSH_BYTES)
        // schema_version is a VARCHAR carrying the spec's semver ("1.0.0"), not an int;
        // migrated_from_schema_version stays an int (the legacy object-model vintage, a
        // different number). No reference_point_* columns: the spec moved that record to
        // the optional eav.model file, which this producer does not write (see below).
        , meta(File(dir, base, "envelope.meta"),
               { Str("schema_version"), Str("produced_by"), Str("producer_version"),
                 Str("sdk_name"), Str("sdk_version"), I32("migrated_from_schema_version") })
        , relTypes(File(dir, base, "envelope.rel_types"),
                   { I32("rel"), Str("name"), Str("src_ns"), Str("dst_ns"), Str("status") })
        , nodeKinds(File(dir, base, "envelope.node_kinds"), { I32("kind"), Str("name"), Str("subtype_values") })
        , types(File(dir, base, "eav.types"), { I32("type_index"), Str("type_key") })
        , typeEav(File(dir, base, "eav.type_eav"),
                  { I32("type_index"), I32("path_index"), Str("value_string"), F64("value_double"),
                    Bool("value_boolean"), Str("unit"), Str("internal_definition_name") })
        , objectType(File(dir, base, "eav.object_type"), { I32("object_index"), I32("type_index") })
    {
    }

    static std::string FileName(const std::string& base, const char* suffix)
    {
        return base + "." + suffix + ".parquet";
    }

    static std::string File(const std::filesystem::path& dir, const std::string& base, const char* suffix)
    {
        return Utf8Path::ToUtf8(dir / FileName(base, suffix));
    }

    // basename suffix -> table, for the ok()-check and Complete() file map.
    std::vector<std::pair<const char*, minipq::Table*>> All()
    {
        return {
            { "geometries", &geometries },
            { "eav.objects", &objects },
            { "eav.paths", &paths },
            { "eav.eav", &eav },
            { "eav.types", &types },
            { "eav.type_eav", &typeEav },
            { "eav.object_type", &objectType },
            { "envelope.nodes", &nodes },
            { "envelope.relations", &relations },
            { "envelope.scene_views", &sceneViews },
            { "envelope.meta", &meta },
            { "envelope.rel_types", &relTypes },
            { "envelope.node_kinds", &nodeKinds },
        };
    }
};

BundleWriter::BundleWriter(const std::string& outputDir, const std::string& baseName, const std::string& producerVersion)
    : _outputDir(outputDir), _baseName(baseName), _producerVersion(producerVersion)
{
    const std::filesystem::path dir = Utf8Path::FromUtf8(outputDir);
    std::filesystem::create_directories(dir);

    _tables = std::make_unique<BundleTables>(dir, baseName);
    for (const auto& t : _tables->All())
    {
        if (!t.second->ok())
            throw std::runtime_error(
                "BundleWriter: cannot create " + BundleTables::FileName(_baseName, t.first) + " in " + outputDir);
    }

    WriteVocabTables();
}

BundleWriter::~BundleWriter() = default;

void BundleWriter::WriteVocabTables()
{
    // meta + rel/kind vocab, from the vendored generated spec (Libs/bundlespec).
    // These three tables are excluded from the spec's column codegen (they are the
    // catalog, not model data), so their ordinals are hand-written here — as they are
    // in the SDK's EnvelopeWriter and the native extractors' envelope_catalog.h.
    _tables->meta.putStr(0, bundlespec::kSchemaVersion);
    _tables->meta.putStr(1, "archicad"); // producer slug, as rvextract/nwextract/teklaextract
    if (_producerVersion.empty())
        _tables->meta.putStrNull(2);
    else
        _tables->meta.putStr(2, _producerVersion);
    // No Speckle SDK in this path — the C++ connector writes bundles directly and the
    // embedded frontend does the upload, so there is no SDK name/version to record.
    _tables->meta.putStrNull(3);
    _tables->meta.putStrNull(4);
    _tables->meta.putIntNull(5); // nothing migrated: authored at the current schema
    _tables->meta.endRow();
    // No reference-point record: we convert at the internal origin and never re-base
    // geometry. The spec's home for it is now model-scoped eav rows in the optional
    // eav.model file (referencePoint.kind/.transform/.units); no rows means internal
    // origin, so a producer that never re-bases writes no file at all.

    for (const auto& r : bundlespec::kRelTypes)
    {
        _tables->relTypes.putInt(0, r.id);
        _tables->relTypes.putStr(1, r.name);
        if (r.src_ns)
            _tables->relTypes.putStr(2, r.src_ns);
        else
            _tables->relTypes.putStrNull(2);
        if (r.dst_ns)
            _tables->relTypes.putStr(3, r.dst_ns);
        else
            _tables->relTypes.putStrNull(3);
        // status is what makes the catalog self-describing: without it a consumer
        // cannot tell a live relation from a reserved one (e.g. SOLID).
        _tables->relTypes.putStr(4, r.status);
        _tables->relTypes.endRow();
    }
    for (const auto& k : bundlespec::kNodeKinds)
    {
        _tables->nodeKinds.putInt(0, k.id);
        _tables->nodeKinds.putStr(1, k.name);
        // CONTAINER's allowed subtype set; NULL for every other kind.
        if (k.subtype_values)
            _tables->nodeKinds.putStr(2, k.subtype_values);
        else
            _tables->nodeKinds.putStrNull(2);
        _tables->nodeKinds.endRow();
    }
}

int BundleWriter::InternObject(const std::string& applicationId)
{
    auto it = _objectIndex.find(applicationId);
    if (it != _objectIndex.end())
        return it->second;

    const int k = static_cast<int>(_objectIndex.size());
    _objectIndex.emplace(applicationId, k);

    _tables->objects.putInt(col::objects::object_index, k);
    _tables->objects.putStr(col::objects::application_id, applicationId);
    _tables->objects.endRow();
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
        _tables->paths.putInt(col::paths::path_index, pathK);
        _tables->paths.putStr(col::paths::path, path);
        _tables->paths.endRow();
    }

    const std::string type = InferType(value);
    const std::string text = ToText(value);

    auto& eav = _tables->eav;
    eav.putInt(col::eav::object_index, objectK);
    eav.putInt(col::eav::path_index, pathK);
    eav.putStr(col::eav::value_string, text);

    std::optional<double> valueDouble;
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
            valueDouble = num;
    }
    eav.putDouble(col::eav::value_double, valueDouble);

    std::optional<bool> valueBoolean;
    if (type == "boolean")
    {
        // Case-insensitive, matching the SDK's bool.TryParse semantics — Archicad
        // extractors historically emitted "True"/"False" with a capital.
        std::string lower = text;
        for (auto& c : lower)
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        valueBoolean = (lower == "true");
    }
    eav.putBool(col::eav::value_boolean, valueBoolean);

    PutStrOpt(eav, col::eav::unit, units);
    PutStrOpt(eav, col::eav::internal_definition_name, internalDefinitionName);
    eav.endRow();
}

void BundleWriter::AddProperties(
    const std::string& applicationId,
    const EavLeaves& properties,
    const std::vector<std::pair<std::string, nlohmann::json>>& rootScalars)
{
    const int objectK = InternObject(applicationId);

    for (const auto& kv : rootScalars)
    {
        if (IsScalar(kv.second))
            AddEavRow(objectK, kv.first, kv.second, nullptr, nullptr);
    }

    for (const EavLeaf& leaf : properties)
    {
        const std::string* units = leaf.units ? &*leaf.units : nullptr;
        const std::string* idn = leaf.internalDefinitionName ? &*leaf.internalDefinitionName : nullptr;

        if (leaf.value.is_array())
        {
            // Archicad — unlike Revit, which the SDK's array-skipping walk was shaped
            // around — emits genuinely multi-valued properties as JSON arrays (native
            // List / Multiple-Choice Enumeration collection types, and IFC List /
            // Enumerated properties). The EAV model is one value per row, so we collapse
            // the elements into a single comma-separated string to preserve them rather
            // than drop the whole property. (IFC bounded ranges are split into lower/upper
            // rows upstream, so they never reach here as an array.)
            const std::string joined = JoinArrayScalars(leaf.value);
            if (!joined.empty())
                AddEavRow(objectK, leaf.path, nlohmann::json(joined), units, idn);
            continue;
        }

        if (IsScalar(leaf.value))
            AddEavRow(objectK, leaf.path, leaf.value, units, idn);
        // non-scalars never reach here (the converter-side flatten filters them)
    }
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

    auto& geometries = _tables->geometries;
    geometries.putInt(col::geometries::geometry_index, k);
    geometries.putBinary(col::geometries::content, sgeoBlob.data(), static_cast<std::int64_t>(sgeoBlob.size()));
    geometries.putStr(col::geometries::id, id);
    geometries.putStr(col::geometries::type, typeName);
    geometries.endRow();
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

// Appends one row to nodes with only the kind-relevant columns set. Column
// positions come from the generated spec constants, so an upstream insertion
// shifts these automatically (see bundle_cols.h).
static void AppendNodeRow(
    minipq::Table& nodes,
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
    const int* emissive,
    const double* ior,
    const double* elevation)
{
    nodes.putInt(col::nodes::id, id);
    nodes.putInt(col::nodes::kind, kind);
    PutStrOpt(nodes, col::nodes::name, name);
    PutIntOpt(nodes, col::nodes::def_ref, defRef);
    PutStrOpt(nodes, col::nodes::transform, transform);
    PutStrOpt(nodes, col::nodes::units, units);
    PutStrOpt(nodes, col::nodes::subtype, subtype);
    PutIntOpt(nodes, col::nodes::argb, argb);
    nodes.putDouble(col::nodes::opacity, Opt(opacity));
    nodes.putDouble(col::nodes::metalness, Opt(metalness));
    nodes.putDouble(col::nodes::roughness, Opt(roughness));
    PutIntOpt(nodes, col::nodes::emissive, emissive);
    nodes.putDouble(col::nodes::ior, Opt(ior));
    nodes.putDouble(col::nodes::elevation, Opt(elevation));
    nodes.endRow();
}

int BundleWriter::AddMaterial(
    const std::string& materialKey, const std::string& name, int argb, double opacity, double metalness, double roughness,
    const int* emissive)
{
    bool isNew;
    const int k = InternNode("mat:" + materialKey, isNew);
    if (isNew)
    {
        // ior stays NULL: Archicad surfaces have no index-of-refraction concept,
        // which is exactly what the spec's "NULL = the host has no IOR" means.
        AppendNodeRow(
            _tables->nodes, k, static_cast<int>(bundlespec::NodeKind::MATERIAL),
            name.empty() ? nullptr : &name, nullptr, nullptr, nullptr, nullptr, &argb, &opacity, &metalness, &roughness,
            emissive, nullptr, nullptr);
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
            _tables->nodes, k, static_cast<int>(bundlespec::NodeKind::LEVEL),
            &name, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &elevation);
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
            _tables->nodes, k, static_cast<int>(bundlespec::NodeKind::CONTAINER),
            &name, parentK, nullptr, nullptr, &subtype, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
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
            _tables->nodes, k, static_cast<int>(bundlespec::NodeKind::CONTAINER),
            &name, parentK, nullptr, nullptr, &subtype, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    return k;
}

int BundleWriter::AddDefinition(const std::string& definitionKey, const std::string& name)
{
    bool isNew;
    const int k = InternNode("def:" + definitionKey, isNew);
    if (isNew)
    {
        AppendNodeRow(
            _tables->nodes, k, static_cast<int>(bundlespec::NodeKind::DEFINITION),
            &name, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    return k;
}

int BundleWriter::AddInstance(const std::string& placementKey, int defK, const std::array<double, 16>& transform, const std::string& units)
{
    bool isNew;
    const int k = InternNode("inst:" + placementKey, isNew);
    if (isNew)
    {
        const std::string tf = FormatTransform(transform);
        AppendNodeRow(
            _tables->nodes, k, static_cast<int>(bundlespec::NodeKind::INSTANCE),
            nullptr, &defK, &tf, &units, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
    }
    return k;
}

void BundleWriter::AddRelation(bundlespec::Rel rel, int src, int dst, int ord)
{
    auto& relations = _tables->relations;
    relations.putInt(col::relations::rel, static_cast<int>(rel));
    relations.putInt(col::relations::src, src);
    relations.putInt(col::relations::dst, dst);
    relations.putInt(col::relations::ord, ord);
    relations.endRow();
}

void BundleWriter::Display(int objectK, int geometryK, int ord) { AddRelation(bundlespec::Rel::DISPLAY, objectK, geometryK, ord); }
void BundleWriter::Subelement(int parentObjectK, int childObjectK, int ord) { AddRelation(bundlespec::Rel::SUBELEMENT, parentObjectK, childObjectK, ord); }
void BundleWriter::Defines(int definitionK, int geometryK, int ord) { AddRelation(bundlespec::Rel::DEFINES, definitionK, geometryK, ord); }
void BundleWriter::DisplayInstance(int objectK, int instanceK, int ord) { AddRelation(bundlespec::Rel::DISPLAY_INSTANCE, objectK, instanceK, ord); }
void BundleWriter::HasMaterial(int geometryK, int materialK) { AddRelation(bundlespec::Rel::HAS_MATERIAL, geometryK, materialK, 0); }
void BundleWriter::HasColor(int srcK, int colorK) { AddRelation(bundlespec::Rel::HAS_COLOR, srcK, colorK, 0); }
void BundleWriter::OnLevel(int objectK, int levelK) { AddRelation(bundlespec::Rel::ON_LEVEL, objectK, levelK, 0); }
void BundleWriter::InCollection(int objectK, int collectionK, int ord) { AddRelation(bundlespec::Rel::IN_COLLECTION, objectK, collectionK, ord); }
void BundleWriter::InModel(int objectK, int modelK, int ord) { AddRelation(bundlespec::Rel::IN_MODEL, objectK, modelK, ord); }
void BundleWriter::InGroup(int objectK, int groupK, int ord) { AddRelation(bundlespec::Rel::IN_GROUP, objectK, groupK, ord); }
void BundleWriter::InRoom(int objectK, int roomK, int ord) { AddRelation(bundlespec::Rel::IN_ROOM, objectK, roomK, ord); }
void BundleWriter::Bounds(int boundingObjectK, int roomObjectK, int ord) { AddRelation(bundlespec::Rel::BOUNDS, boundingObjectK, roomObjectK, ord); }
void BundleWriter::HostedOn(int hostedObjectK, int hostObjectK) { AddRelation(bundlespec::Rel::HOSTED_ON, hostedObjectK, hostObjectK, 0); }
void BundleWriter::ConnectsTo(int sourceObjectK, int targetObjectK, int scope) { AddRelation(bundlespec::Rel::CONNECTS_TO, sourceObjectK, targetObjectK, scope); }

void BundleWriter::AddSceneView(int view, const std::string& name, bool isDefault, const std::vector<SceneViewTier>& tiers)
{
    auto& sceneViews = _tables->sceneViews;
    for (size_t ord = 0; ord < tiers.size(); ord++)
    {
        sceneViews.putInt(col::scene_views::view, view);
        sceneViews.putStr(col::scene_views::name, name);
        sceneViews.putBool(col::scene_views::is_default, isDefault);
        sceneViews.putInt(col::scene_views::ord, static_cast<int>(ord));
        sceneViews.putStr(col::scene_views::source, tiers[ord].source);
        sceneViews.putStr(col::scene_views::ref, tiers[ord].ref);
        sceneViews.endRow();
    }
}

int BundleWriter::TableCount()
{
    return 13; // the fixed bundle table set (BundleTables::All)
}

std::map<std::string, std::string> BundleWriter::Complete(
    const std::function<void(int done, int total)>& progress)
{
    if (_completed)
        throw std::runtime_error("BundleWriter::Complete called twice");
    _completed = true;

    const std::filesystem::path dir = Utf8Path::FromUtf8(_outputDir);
    std::map<std::string, std::string> files;
    const auto all = _tables->All();
    int done = 0;
    for (const auto& t : all)
    {
        t.second->complete();
        const std::string fileName = BundleTables::FileName(_baseName, t.first);
        // complete() runs the post-close size gate (on-disk bytes must equal the
        // writer's accounting) on top of any earlier write/compress failure.
        if (!t.second->ok())
            throw std::runtime_error("BundleWriter: failed to write " + fileName);
        files[fileName] = BundleTables::File(dir, _baseName, t.first);
        ++done;
        if (progress)
            progress(done, static_cast<int>(all.size()));
    }
    return files;
}
