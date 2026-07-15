#pragma once
// BundleWriter — owns every parquet table of the Speckle 4.0 bundle and the vocabulary for
// writing into them. It replaces the pile of capturing lambdas (addNode/addRel/writeRow/
// intern…) and loose counters that used to live in main(): an unnamed object wearing a
// trench coat, now given a name.
//
// Tables owned: eav.{objects,paths,eav,types,type_eav,object_type}, the geometry shards
// (GeomSharder), and envelope.{nodes,relations}. The constant catalog sidecars
// (meta/node_kinds/rel_types/scene_views) are NOT here — see envelope_catalog.h.
//
// Node/geometry K are dense, minted in first-write order; the caller keeps the dedup maps
// (geomHash → node K, etc.) and asks the writer to mint+write on a miss, so K assignment
// order is identical to the original inline code. Output is byte-for-byte unchanged — gated
// by the snowden md5 baseline.

#include "parquet_table.h"
#include "geom_sharder.h"
#include "eav_flatten.h"
#include "fragment_keys.h"  // kKeysSuffix/keysSchema — the fragment-keys sidecar contract

// Generated from the sibling generated/cpp of this repo:
//   envelope_spec.h  — Rel / NodeKind enums + kSchemaVersion
//   bundle_schemas.h — one arrow::Schema factory per table (the SoT for shapes)
#include "envelope_spec.h"
#include "bundle_schemas.h"

#include <arrow/api.h>
#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

class BundleWriter {
  static std::shared_ptr<arrow::Field> S(const char* n) {
    return arrow::field(n, arrow::utf8());
  }
  static std::shared_ptr<arrow::Field> I(const char* n) {
    return arrow::field(n, arrow::int32());
  }
  static std::shared_ptr<arrow::Schema> eavSchema(const char* key) {
    return arrow::schema({I(key), I("path_index"), S("value_string"),
                          arrow::field("value_double", arrow::float64()),
                          arrow::field("value_boolean", arrow::boolean()),
                          S("unit"), S("internal_definition_name")});
  }
  static std::optional<bool> parseBool(const std::string& s) {
    std::string t = eav::trim(s);
    for (auto& c : t) c = (char)std::tolower((unsigned char)c);
    if (t == "true") return true;
    if (t == "false") return false;
    return std::nullopt;
  }

  PqTable objectsT_, pathsT_, eavT_, typesT_, typeEavT_, objectTypeT_,
      envNodesT_, envRelsT_;
  GeomSharder geomT_;
  // Fragment mode (fork/pool workers): natural-key sidecar so bmerge::merge can
  // dedupe env nodes / geometries across workers. Null unless enabled.
  std::unique_ptr<PqTable> keysT_;
  std::string keysPath_;
  std::unordered_map<std::string, int> objIndex_, pathIndex_, typeIndex_;
  int nextNodeK_ = 0, nextGeomK_ = 0;
  long long eavRows_ = 0, typeEavRows_ = 0, objectTypeRows_ = 0;
  long long envNodes_ = 0, envRels_ = 0, geomRows_ = 0, levelNodes_ = 0;

  int internPath(const std::string& p) {
    auto it = pathIndex_.find(p);
    if (it != pathIndex_.end()) return it->second;
    int idx = (int)pathIndex_.size();
    pathIndex_.emplace(p, idx);
    pathsT_.putInt(0, idx);
    pathsT_.putStr(1, p);
    pathsT_.endRow();
    return idx;
  }
  void writeRowTo(PqTable& T, int key, const EavRow& r) {
    T.putInt(0, key);
    T.putInt(1, internPath(r.path));
    T.putStr(2, r.valueText);
    T.putDouble(3, r.valueNum);
    T.putBool(4, r.type == "boolean" ? parseBool(r.valueText) : std::nullopt);
    if (r.units)
      T.putStr(5, *r.units);
    else
      T.putStrNull(5);
    if (r.idn)
      T.putStr(6, *r.idn);
    else
      T.putStrNull(6);
    T.endRow();
  }

 public:
  BundleWriter(const std::string& outdir, const std::string& base,
               int64_t geomShardCap)
      // Schemas come from the generated spec (bundle_schemas.h) — single source of
      // truth for table shapes. Column order/names/types are identical to the prior
      // hand-written schemas except nodes, which now carries `subtype`.
      : objectsT_(outdir + "/" + base + ".eav.objects.parquet",
                  bundlespec::objectsSchema()),
        pathsT_(outdir + "/" + base + ".eav.paths.parquet",
                bundlespec::pathsSchema()),
        eavT_(outdir + "/" + base + ".eav.eav.parquet",
              bundlespec::eavSchema()),
        typesT_(outdir + "/" + base + ".eav.types.parquet",
                bundlespec::typesSchema()),
        typeEavT_(outdir + "/" + base + ".eav.type_eav.parquet",
                  bundlespec::typeEavSchema()),
        objectTypeT_(outdir + "/" + base + ".eav.object_type.parquet",
                     bundlespec::objectTypeSchema()),
        envNodesT_(outdir + "/" + base + ".envelope.nodes.parquet",
                   bundlespec::nodesSchema()),
        envRelsT_(outdir + "/" + base + ".envelope.relations.parquet",
                  bundlespec::relationsSchema()),
        geomT_(outdir, base, bundlespec::geometriesSchema(), geomShardCap),
        keysPath_(outdir + "/" + base + bmerge::kKeysSuffix) {}

  // Fragment mode: record (space, k, dedup key) for every keyed mint so the parent's
  // merge can unify K spaces across workers. Call right after construction.
  void enableFragmentKeys() {
    keysT_ = std::make_unique<PqTable>(keysPath_, bmerge::keysSchema());
  }
  bool fragmentMode() const { return keysT_ != nullptr; }
  // Next node K to be minted — lets producers record a definition subtree's
  // exclusive end for the merge's losing-subtree drop (payload "end:<k>").
  int nodeCount() const { return nextNodeK_; }
  // Object handle → local objK sidecar row (Revit: feeds the merge's global
  // handle map for cross-worker topology resolution).
  void logObjHandle(int objK, unsigned long long handle) {
    if (!keysT_) return;
    keysT_->putInt(0, bmerge::kSpaceObjHandle);
    keysT_->putInt(1, objK);
    keysT_->putStr(2, std::to_string(handle));
    keysT_->putInt64(3, 0);
    keysT_->putStr(4, std::string());
    keysT_->endRow();
  }
  // payload: optional content-winner data for nodes whose CONTENT is sighting-
  // dependent (LEVEL name/elevation); ord = the min ordinal that content was
  // seen at. Plain identity rows pass ord 0 / payload "".
  void logNodeKey(int k, const std::string& key, uint64_t ord = 0,
                  const std::string& payload = std::string()) {
    if (!keysT_) return;
    keysT_->putInt(0, bmerge::kSpaceNode);
    keysT_->putInt(1, k);
    keysT_->putStr(2, key);
    keysT_->putInt64(3, (int64_t)ord);
    keysT_->putStr(4, payload);
    keysT_->endRow();
  }
  // ord = the hash's MINIMUM global DFS ordinal over every sighting; matKey =
  // the material content at that minimum; k = -1 records an empty-blob CLAIM
  // (no geometry row) — see bundle_merge.h.
  void logGeomKey(int k, const std::string& key, uint64_t ord,
                  const std::string& matKey) {
    if (!keysT_) return;
    keysT_->putInt(0, bmerge::kSpaceGeom);
    keysT_->putInt(1, k);
    keysT_->putStr(2, key);
    keysT_->putInt64(3, (int64_t)ord);
    keysT_->putStr(4, matKey);
    keysT_->endRow();
  }

  bool ok() const {
    return objectsT_.ok() && pathsT_.ok() && eavT_.ok() && typesT_.ok() &&
           typeEavT_.ok() && objectTypeT_.ok() && geomT_.ok() &&
           envNodesT_.ok() && envRelsT_.ok();
  }

  // ── eav ────────────────────────────────────────────────────────────────────
  int internObject(const std::string& app) {
    auto it = objIndex_.find(app);
    if (it != objIndex_.end()) return it->second;
    int idx = (int)objIndex_.size();
    objIndex_.emplace(app, idx);
    objectsT_.putInt(0, idx);
    objectsT_.putStr(1, app);
    objectsT_.endRow();
    return idx;
  }
  void writeInstanceEav(int objK, const std::vector<EavRow>& rows) {
    for (auto& r : rows) {
      writeRowTo(eavT_, objK, r);
      ++eavRows_;
    }
  }
  // Type-scoped group: dedup by precomputed content-hash key → one type_eav record + an
  // object_type weak ref. Caller computes the key (content hashing stays in main).
  void writeType(int objK, const std::string& key,
                 const std::vector<EavRow>& trows) {
    auto tit = typeIndex_.find(key);
    int tIdx;
    if (tit == typeIndex_.end()) {
      tIdx = (int)typeIndex_.size();
      typeIndex_.emplace(key, tIdx);
      typesT_.putInt(0, tIdx);
      typesT_.putStr(1, key);
      typesT_.endRow();
      for (auto& r : trows) {
        writeRowTo(typeEavT_, tIdx, r);
        ++typeEavRows_;
      }
    } else
      tIdx = tit->second;
    objectTypeT_.putInt(0, objK);
    objectTypeT_.putInt(1, tIdx);
    objectTypeT_.endRow();
    ++objectTypeRows_;
  }

  // ── envelope nodes / relations / geometry ────────────────────────────────────
  // Mint a node K (first-write order) and write the row. Only MATERIAL fills argb/opacity/
  // metalness/roughness; elevation is always null here (use addLevelNode for LEVEL).
  // roughness defaults to the historical fixed 1.0; producers with real surface data
  // (archicad: 1 − shining/100) pass it explicitly. Metalness stays fixed at 0.0 —
  // no producer has real metalness today.
  int addNode(bundlespec::NodeKind kind, const std::string* name, int defRef,
              const std::string* xf, const std::string* units,
              const std::string* subtype, bool isMat, int argb, double opacity,
              double roughness = 1.0) {
    int id = nextNodeK_++;
    envNodesT_.putInt(0, id);
    envNodesT_.putInt(1, (int)kind);
    if (name)
      envNodesT_.putStr(2, *name);
    else
      envNodesT_.putStrNull(2);
    if (defRef >= 0)
      envNodesT_.putInt(3, defRef);
    else
      envNodesT_.putIntNull(3);
    if (xf)
      envNodesT_.putStr(4, *xf);
    else
      envNodesT_.putStrNull(4);
    if (units)
      envNodesT_.putStr(5, *units);
    else
      envNodesT_.putStrNull(5);
    if (subtype)
      envNodesT_.putStr(6, *subtype);  // CONTAINER polymorphism (was the units overload)
    else
      envNodesT_.putStrNull(6);
    if (isMat) {
      envNodesT_.putInt(7, argb);
      envNodesT_.putDouble(8, opacity);
      envNodesT_.putDouble(9, 0.0);
      envNodesT_.putDouble(10, roughness);
    } else {
      envNodesT_.putIntNull(7);
      envNodesT_.putDouble(8, std::nullopt);
      envNodesT_.putDouble(9, std::nullopt);
      envNodesT_.putDouble(10, std::nullopt);
    }
    envNodesT_.putDouble(11, std::nullopt);  // elevation
    envNodesT_.endRow();
    ++envNodes_;
    return id;
  }
  // LEVEL node (kind 5): carries name + elevation, no transform/units/material channels.
  int addLevelNode(const std::string* name, std::optional<double> elevation) {
    int id = nextNodeK_++;
    envNodesT_.putInt(0, id);
    envNodesT_.putInt(1, (int)bundlespec::NodeKind::LEVEL);
    if (name)
      envNodesT_.putStr(2, *name);
    else
      envNodesT_.putStrNull(2);
    envNodesT_.putIntNull(3);
    envNodesT_.putStrNull(4);
    envNodesT_.putStrNull(5);  // def_ref, transform, units
    envNodesT_.putStrNull(6);  // subtype
    envNodesT_.putIntNull(7);  // argb
    envNodesT_.putDouble(8, std::nullopt);
    envNodesT_.putDouble(9, std::nullopt);
    envNodesT_.putDouble(10, std::nullopt);
    envNodesT_.putDouble(11, elevation);
    envNodesT_.endRow();
    ++envNodes_;
    ++levelNodes_;
    return id;
  }
  void addRel(int rel, int src, int dst, int ord) {
    envRelsT_.putInt(0, rel);
    envRelsT_.putInt(1, src);
    envRelsT_.putInt(2, dst);
    envRelsT_.putInt(3, ord);
    envRelsT_.endRow();
    ++envRels_;
  }
  // Mint a geometry K and append the SGEO blob to the (sharded) geometries table.
  int addGeometry(const std::string& id, const uint8_t* blob, int64_t len) {
    int k = nextGeomK_++;
    geomT_.add(k, blob, len, id);
    ++geomRows_;
    return k;
  }

  void finalize() {
    if (keysT_) keysT_->complete();
    objectsT_.complete();
    pathsT_.complete();
    eavT_.complete();
    typesT_.complete();
    typeEavT_.complete();
    objectTypeT_.complete();
    geomT_.complete();
    envNodesT_.complete();
    envRelsT_.complete();
  }

  // ── stats (for RESULT_JSON) ──────────────────────────────────────────────────
  long long eavRows() const { return eavRows_; }
  size_t objectCount() const { return objIndex_.size(); }
  size_t pathCount() const { return pathIndex_.size(); }
  size_t typeCount() const { return typeIndex_.size(); }
  long long geomRows() const { return geomRows_; }
  int geomShardCount() const { return geomT_.shardCount(); }
  long long typeEavRows() const { return typeEavRows_; }
  long long objectTypeRows() const { return objectTypeRows_; }
  long long levelNodes() const { return levelNodes_; }
  long long envNodes() const { return envNodes_; }
  long long envRels() const { return envRels_; }
};
