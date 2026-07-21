#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "json.hpp"
#include "EavLeaf.h"
#include "envelope_spec.h"

struct BundleTables;

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
// node) and appends rows straight into one minipq parquet writer per table,
// each already open at its final {baseName}.<group>.<table>.parquet path with
// Zstd compression — the bundle-spec (schema_version 5) wire format.
//
// minipq (Libs/minipq) is the parquet engine: an in-tree, dependency-free
// writer sized to exactly the bundle subset, statically compiled into the
// .apx (it replaced the delay-loaded duckdb.dll). Rows stream to disk in
// bounded row groups instead of accumulating in an in-memory database.
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

    // Writes rootScalars + the pre-flattened property leaves as EAV rows.
    // The flattening itself (paths, {name,value} collapse, depth cap) happens
    // in the converter (GetElementProperties) — no nested tree reaches here.
    void AddProperties(
        const std::string& applicationId,
        const EavLeaves& properties,
        const std::vector<std::pair<std::string, nlohmann::json>>& rootScalars);

    // ── geometry namespace ────────────────────────────────────────────
    // Stores an SGEO blob under a dense geometry K on first sight (id = SHA256
    // hex of the content, type = primitive name). Returns the K either way.
    int AddGeometrySgeo(
        const std::string& geometryApplicationId,
        const std::vector<std::uint8_t>& sgeoBlob,
        const std::string& typeName = "mesh");

    // ── node namespace (value entities) ───────────────────────────────
    int AddMaterial(const std::string& materialKey, const std::string& name, int argb, double opacity, double metalness, double roughness);
    int AddLevel(const std::string& levelKey, const std::string& name, double elevation);
    int AddCollection(const std::string& collectionKey, const std::string& name, const int* parentK, const std::string& subtype);
    int AddContainer(const std::string& containerKey, const std::string& name, const int* parentK, const std::string& subtype);

    // Instancing nodes. A DEFINITION is shared geometry (linked via DEFINES); an INSTANCE
    // is one placement of a definition (its transform + a def_ref back to the definition K),
    // referenced from an object via DISPLAY_INSTANCE. transform is 16 row-major doubles
    // (M11..M44), serialized to the nodes.transform CSV the SDK reader parses.
    int AddDefinition(const std::string& definitionKey, const std::string& name);
    int AddInstance(const std::string& placementKey, int defK, const std::array<double, 16>& transform, const std::string& units);

    // ── relations ─────────────────────────────────────────────────────
    void Display(int objectK, int geometryK, int ord);
    void Subelement(int parentObjectK, int childObjectK, int ord);
    void Defines(int definitionK, int geometryK, int ord);
    void DisplayInstance(int objectK, int instanceK, int ord);
    void HasMaterial(int geometryK, int materialK);
    void HasColor(int srcK, int colorK);
    void OnLevel(int objectK, int levelK);
    void InCollection(int objectK, int collectionK, int ord);
    void InModel(int objectK, int modelK, int ord);

    // ── scene views ───────────────────────────────────────────────────
    void AddSceneView(int view, const std::string& name, bool isDefault, const std::vector<SceneViewTier>& tiers);

    // Flushes everything and writes the parquet files. Returns basename -> full path
    // for the uploader. Must be called exactly once. progress (optional) is
    // invoked after each finalized table with (tablesDone, tableCount).
    std::map<std::string, std::string> Complete(
        const std::function<void(int done, int total)>& progress = nullptr);

    // Number of parquet files a bundle consists of (progress phase sizing).
    static int TableCount();

    int ObjectCount() const { return static_cast<int>(_objectIndex.size()); }

private:
    void AddRelation(bundlespec::Rel rel, int src, int dst, int ord);
    int InternNode(const std::string& key, bool& isNew);
    void AddEavRow(int objectK, const std::string& path, const nlohmann::json& value,
                   const std::string* units, const std::string* internalDefinitionName);
    void WriteVocabTables();

    std::string _outputDir;
    std::string _baseName;

    // One minipq::Table per bundle file (opaque here so minipq.h stays out of this header).
    std::unique_ptr<BundleTables> _tables;

    // Intern tables (hot per-row lookups; K assignment order is insertion order,
    // so the container's own ordering is irrelevant).
    std::unordered_map<std::string, int> _objectIndex;
    std::unordered_map<std::string, int> _pathIndex;
    std::unordered_map<std::string, int> _geometryIndex;
    std::unordered_map<std::string, int> _nodeIndex;

    bool _completed = false;
};
