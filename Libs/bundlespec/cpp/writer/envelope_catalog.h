#pragma once
// Envelope catalog tables — the constant, self-describing schema sidecars of the bundle
// (they carry no model data, just the vocabulary a consumer needs to read the graph):
//   • meta        — schema version + producer string
//   • node_kinds  — NodeKind enum → name
//   • rel_types   — RelKind enum → name + src/dst namespace
//   • scene_views — the producer-authored default view projection (SOT §8)
// Kept byte-for-byte identical to the managed EnvelopeWriter. Pulled out of main() so the
// orchestrator reads as phases, not table-pushing.

#include "parquet_table.h"

// Generated catalog rows (kRelTypes / kNodeKinds) + kSchemaVersion, from the
// spec (../speckle-bundle-spec). The vocabulary is no longer hand-written here.
#include "envelope_spec.h"

#include <arrow/api.h>
#include <string>
#include <vector>

namespace envcat {
inline std::shared_ptr<arrow::Field> S(const char* n) {
  return arrow::field(n, arrow::utf8());
}
inline std::shared_ptr<arrow::Field> I(const char* n) {
  return arrow::field(n, arrow::int32());
}

// meta + node_kinds + rel_types: pure constants (match EnvelopeWriter exactly).
inline void writeCatalogTables(const std::string& outdir,
                               const std::string& base,
                               const std::string& producer) {
  {
    // produced_by identifies the source-format producer (nwextract=navis,
    // rvextract=revit, speckleifc=ifc) so a bundle self-describes which converter
    // — and therefore which source format — emitted it.
    PqTable meta(outdir + "/" + base + ".envelope.meta.parquet",
                 arrow::schema({I("schema_version"), S("produced_by")}));
    meta.putInt(0, bundlespec::kSchemaVersion);
    meta.putStr(1, producer.c_str());
    meta.endRow();
    meta.complete();
  }
  {
    // node_kinds: shipped rows (live + reserved) from the generated catalog.
    PqTable nk(outdir + "/" + base + ".envelope.node_kinds.parquet",
               arrow::schema({I("kind"), S("name")}));
    for (const auto& k : bundlespec::kNodeKinds) {
      nk.putInt(0, k.id);
      nk.putStr(1, k.name);
      nk.endRow();
    }
    nk.complete();
  }
  {
    // rel_types: shipped rows (live + reserved) from the generated catalog. Retired
    // ids are omitted (and never reused). src/dst namespaces ride along.
    PqTable rt(outdir + "/" + base + ".envelope.rel_types.parquet",
               arrow::schema({I("rel"), S("name"), S("src_ns"), S("dst_ns")}));
    for (const auto& r : bundlespec::kRelTypes) {
      rt.putInt(0, r.id);
      rt.putStr(1, r.name);
      if (r.src_ns) rt.putStr(2, r.src_ns); else rt.putStrNull(2);
      if (r.dst_ns) rt.putStr(3, r.dst_ns); else rt.putStrNull(3);
      rt.endRow();
    }
    rt.complete();
  }
}

// One scene-view tier: source is "rel" (ref = a Rel id as decimal text) or "eav"
// (ref = an eav path). Tiers are ordered outermost-first.
struct SceneViewTier {
  std::string source;
  std::string ref;
};

// Generic producer-authored default scene_views projection (SOT §8): write the given
// ordered tier list as the single default view. No-op on an empty list (consumer
// falls back to its own default grouping).
inline void writeSceneViewTiers(const std::string& outdir,
                                const std::string& base,
                                const std::vector<SceneViewTier>& tiers,
                                const std::string& viewName = "Default") {
  if (tiers.empty()) return;
  PqTable sv(outdir + "/" + base + ".envelope.scene_views.parquet",
             arrow::schema({I("view"), S("name"),
                            arrow::field("is_default", arrow::boolean()),
                            I("ord"), S("source"), S("ref")}));
  for (int i = 0; i < (int)tiers.size(); ++i) {
    sv.putInt(0, 0);
    sv.putStr(1, viewName);
    sv.putBool(2, true);
    sv.putInt(3, i);
    sv.putStr(4, tiers[(size_t)i].source);
    sv.putStr(5, tiers[(size_t)i].ref);
    sv.endRow();
  }
  sv.complete();
}

// Source-format-aware convenience wrapper (byte-identical to the pre-consolidation
// converters writer):
//   • federated (>1 model)  ⇒ IN_MODEL (rel 11) is the outermost tier;
//   • nativeRevit           ⇒ Revit's default tiers level → category → family, where category/family
//                              are the BARE root-scalar eav paths the native extractor emits;
//   • anyRevit (Navis-sourced Revit) ⇒ same tiers but Navis buries them under properties.Element.*;
//   • other formats (IFC …) ⇒ TBD — IN_MODEL only when federated, else no table (consumer falls back).
inline void writeSceneViews(const std::string& outdir, const std::string& base,
                            bool federated, bool anyRevit, bool nativeRevit = false) {
  std::vector<SceneViewTier> keys;  // outermost-first
  if (federated)
    keys.push_back({"rel", "11"});  // IN_MODEL (federated: >1 source file)
  if (nativeRevit) {
    keys.push_back({"rel", "7"});  // ON_LEVEL
    keys.push_back({"eav", "category"});
    keys.push_back({"eav", "family"});
  } else if (anyRevit) {
    keys.push_back({"rel", "7"});  // ON_LEVEL
    keys.push_back({"eav", "properties.Element.Category"});
    keys.push_back({"eav", "properties.Element.Family"});
  }
  writeSceneViewTiers(outdir, base, keys);
}
}  // namespace envcat
