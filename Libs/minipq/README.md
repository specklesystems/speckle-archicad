# minipq (vendored)

A minimal, dependency-free (zstd only) **parquet writer + reader** covering
exactly the Speckle bundle subset: flat schemas, nullable
{int32, int64, double, bool, utf8, binary}, ZSTD compression, V1 data pages,
CRC-32 on every page, int32 min/max statistics, ~1MiB page splitting, and a
post-close file-size integrity gate.

- **Source:** copied from `specklesystems/speckle-converters` branch
  `poc/minipq` (PR #15 "minipq: dependency-free parquet IO for the native
  producers"), `native/core/minipq/`.
- **Files:** `minipq.h` (writer), `minipq_reader.h` (reader),
  `thrift_compact.h` (footer encoding), `crc32.h`.
- **Consumers:** `BundleWriter` (send) and `ArtifactReceiver` (receive) in
  the Speckle add-on. Replaced the DuckDB C-API + `duckdb.dll` delay-load.

## Local modifications vs upstream

- **`minipq_io.h` (added):** UTF-8-safe `fopen`/file-size wrappers. The CRT's
  narrow `fopen`/`_stat64` interpret paths in the ANSI codepage; bundle paths
  live under the user's `%TEMP%`/`%APPDATA%`, which may be non-ASCII. Both
  headers now open files through these wrappers.
- `minipq.h` / `minipq_reader.h`: call sites switched to `minipq_io.h`
  (`openUtf8`, `fileSizeUtf8`); no other changes.

When syncing with upstream (e.g. once minipq lands in the shared
speckle-bundle-spec `cpp/` package), re-apply the `minipq_io.h` call sites or
upstream the fix.
