#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "json.hpp"
#include "envelope_spec.h"

struct duckdb_database_wrapper;
struct duckdb_connection_wrapper;

// One ordered grouping tier of a scene-view projection.
// source "rel": ref is a RelKind id as text (e.g. "7" = ON_LEVEL).
// source "eav": ref is an eav attribute key (e.g. "type").
struct SceneViewTier
{
    std::string source; // "rel" | "eav"
    std::string ref;
};

// The Speckle 4.0 artefact-bundle producer — the C++ mirror of the SDK's
// ObjectsArtifactPipeline (speckle-sharp-sdk, Speckle.Objects/Utils). Interns
// string identities into the three dense int32 namespaces (object / geometry /
// node), buffers rows into an in-memory DuckDB, and Complete() COPYs every
// table out as {baseName}.<group>.<table>.parquet with Zstd compression —
// the bundle-spec (schema_version 5) wire format.
//
// DuckDB is the parquet engine on purpose: the spec itself is executable
// DuckDB SQL, the spec validator reads bundles with DuckDB, and the
// amalgamation ships parquet+zstd with zero extra dependencies.
class BundleWriter
{
public:
    // outputDir must exist or be creatable; baseName is the server-pre-allocated versionId.
    BundleWriter(const std::string& outputDir, const std::string& baseName);
    ~BundleWriter();

    BundleWriter(const BundleWriter&) = delete;
    BundleWriter& operator=(const BundleWriter&) = delete;

    // ── object namespace ──────────────────────────────────────────────
    int InternObject(const std::string& applicationId);

    // Flattens rootScalars + the nested properties dict into EAV rows
    // (ports EavExtraction.FlattenProperties: "properties." path prefix,
    // parameter {name,value} pattern, max depth 10, arrays skipped).
    void AddProperties(
        const std::string& applicationId,
        const nlohmann::json& properties,
        const std::vector<std::pair<std::string, nlohmann::json>>& rootScalars);

    // ── geometry namespace ────────────────────────────────────────────
    // Stores an SGEO blob under a dense geometry K on first sight (id = SHA256
    // hex of the content, type = primitive name). Returns the K either way.
    int AddGeometrySgeo(
        const std::string& geometryApplicationId,
        const std::vector<std::uint8_t>& sgeoBlob,
        const std::string& typeName = "mesh");

    // ── node namespace (value entities) ───────────────────────────────
    int AddMaterial(const std::string& materialKey, int argb, double opacity, double metalness, double roughness);
    int AddLevel(const std::string& levelKey, const std::string& name, double elevation);
    int AddCollection(const std::string& collectionKey, const std::string& name, const int* parentK, const std::string& subtype);
    int AddContainer(const std::string& containerKey, const std::string& name, const int* parentK, const std::string& subtype);

    // ── relations ─────────────────────────────────────────────────────
    void Display(int objectK, int geometryK, int ord);
    void Subelement(int parentObjectK, int childObjectK, int ord);
    void HasMaterial(int geometryK, int materialK);
    void HasColor(int srcK, int colorK);
    void OnLevel(int objectK, int levelK);
    void InCollection(int objectK, int collectionK, int ord);
    void InModel(int objectK, int modelK, int ord);

    // ── scene views ───────────────────────────────────────────────────
    void AddSceneView(int view, const std::string& name, bool isDefault, const std::vector<SceneViewTier>& tiers);

    // Flushes everything and writes the parquet files. Returns basename -> full path
    // for the uploader. Must be called exactly once.
    std::map<std::string, std::string> Complete();

    int ObjectCount() const { return static_cast<int>(_objectIndex.size()); }

private:
    void Execute(const std::string& sql);
    void AddRelation(bundlespec::Rel rel, int src, int dst, int ord);
    int InternNode(const std::string& key, bool& isNew);
    void AddEavRow(int objectK, const std::string& path, const nlohmann::json& value,
                   const std::string* units, const std::string* internalDefinitionName);
    void WalkProperties(int objectK, const nlohmann::json& obj, const std::string& prefix, int depth);
    void WriteVocabTables();

    std::string _outputDir;
    std::string _baseName;

    // DuckDB C-API handles (opaque pointers; kept void* so duckdb.h stays out of this header).
    void* _db = nullptr;
    void* _con = nullptr;
    std::map<std::string, void*> _appenders; // table name -> duckdb_appender

    std::map<std::string, int> _objectIndex;
    std::map<std::string, int> _pathIndex;
    std::map<std::string, int> _geometryIndex;
    std::map<std::string, int> _nodeIndex;

    bool _completed = false;
};
