#pragma once
// Fragment-keys sidecar contract — the natural-key sidecar written by fragment-mode
// workers (BundleWriter::enableFragmentKeys) and consumed by the fork/pool merge
// (bundle_merge.h, which lives with the converters). These constants sit in the writer
// package so the writer is self-contained; the merge includes the writer, never the
// other way around.
//
// Moved verbatim from speckle-converters native/core/bundle_merge.h (the merge-only
// kDroppedNode sentinel stays there).

#include <arrow/api.h>

#include <memory>

namespace bmerge {

// Sidecar written by fragment-mode workers (BundleWriter::enableFragmentKeys):
// (space: 0=node 1=geometry, k: the worker-local K, key: the dedup key, ord: the
// item's global DFS ordinal for geometry rows — the merge tie-break; 0 for nodes).
// Geometry rows with k = -1 are CLAIMS without a row (single-run seenGeom claims a
// hash even when the mesh blob is empty); a winning empty claim suppresses the
// hash bundle-wide, exactly as the single-run gate would.
inline constexpr const char* kKeysSuffix = ".fragment_keys.parquet";
inline constexpr int kSpaceNode = 0, kSpaceGeom = 1, kSpaceObjHandle = 2;
inline std::shared_ptr<arrow::Schema> keysSchema() {
  return arrow::schema({arrow::field("space", arrow::int32()),
                        arrow::field("k", arrow::int32()),
                        arrow::field("key", arrow::utf8()),
                        arrow::field("ord", arrow::int64()),
                        arrow::field("mat_key", arrow::utf8())});
}

}  // namespace bmerge
