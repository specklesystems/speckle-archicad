#pragma once
// Geometry parquet sharder. Rolls the geometries artefact across multiple parquet files
// so no single file exceeds the viewer's per-file ceiling (duckdb-wasm wasm32 32-bit file
// offsets / OPFS, ~4 GiB). The cap is on UNCOMPRESSED blob bytes, so the on-disk (zstd)
// shard is always smaller than the cap — guaranteed under the limit regardless of the
// compression ratio.
//
// Contract (shared VERBATIM with the managed SDK GeometriesParquetWriter, C#):
//   • shard 0 keeps the canonical name  "{base}.geometries.parquet"  (a model that fits in
//     one shard is byte-for-byte unchanged from the pre-sharding output),
//   • overflow shards are            "{base}.geometries.{N}.parquet"  (N = 1, 2, …),
//   • roll BEFORE a blob that would push the current shard past the cap (a single blob
//     larger than the whole cap still lands in its own shard, never an empty file ahead),
//   • default cap 1.5 GiB uncompressed (== the SDK's SPECKLE_GEOMETRY_SHARD_MB=1536).
// Consumers read the set via the glob "{base}.geometries*.parquet" (a single-shard model
// matches only the canonical name).
//
// ODA-free: depends only on parquet_table.h (Arrow/Parquet), so it is unit-testable
// standalone without the ODA SDK.

#include "parquet_table.h"

#include <arrow/api.h>
#include <cstdint>
#include <memory>
#include <string>

struct GeomSharder {
  std::string outdir, base;
  std::shared_ptr<arrow::Schema> schema;
  int64_t capBytes;
  std::unique_ptr<PqTable> cur;
  int shard = 0;
  int64_t curBytes = 0;
  long long rows = 0;
  bool good = true;

  GeomSharder(std::string od, std::string b, std::shared_ptr<arrow::Schema> s,
              int64_t cap)
      : outdir(std::move(od)),
        base(std::move(b)),
        schema(std::move(s)),
        capBytes(cap) {
    open();
  }

  void open() {
    std::string name =
        base + ".geometries" +
        (shard == 0 ? std::string() : "." + std::to_string(shard)) + ".parquet";
    cur = std::make_unique<PqTable>(outdir + "/" + name, schema, 200000,
                                    128 * 1024 * 1024);
    curBytes = 0;
    if (!cur->ok()) good = false;
  }

  bool ok() const { return good && cur && cur->ok(); }

  // One geometry row: (geometryIndex, content blob, id, type). Rolls to the next shard
  // first if this blob would push the current shard past the cap.
  void add(int geomK, const uint8_t* blob, int64_t len, const std::string& id) {
    if (curBytes > 0 && curBytes + len > capBytes) {
      cur->complete();
      ++shard;
      open();
    }
    cur->putInt(0, geomK);
    cur->putBinary(1, blob, len);
    cur->putStr(2, id);
    cur->putStr(3, "mesh");
    cur->endRow();
    curBytes += len;
    ++rows;
  }

  int shardCount() const { return shard + 1; }
  void complete() {
    if (cur) cur->complete();
  }
};
