Vendored from speckle-bundle-spec (schema_version 1.0.0), generated/cpp/:
  envelope_spec.h — rel/node-kind vocabulary + catalog rows.
  bundle_cols.h   — named column indices per produced table (no arrow dependency).

bundle_cols.h declares camera_views::near/far, which windef.h defines as macros;
include it before <windows.h> or #undef them first (BundleWriter.cpp does the latter).

Pinned to spec commit e360fcfeeef3354c95c2a3a5554782bae15b783a (2026-08-26).

NOTE: kSchemaVersion is a `const char*` semver string ("1.0.0"), not an int — the
spec collapsed schema_version and the package version into one value, so
envelope.meta.schema_version is a VARCHAR column. Older bundles carry the integers
5 or 1 there; readers must treat the column as text.

The third generated header, bundle_schemas.h, is deliberately NOT vendored: it
returns arrow::Schema objects, and this add-on writes parquet through minipq. The
minipq field lists in BundleWriter.cpp are the hand-maintained equivalent, guarded
by static_asserts against bundle_cols.h's columnCount.

Regenerate with 'npm run generate' in the spec repo and re-copy; do not edit by hand.
Compare against the commit hash above, not the version string: additive vocabulary
edits (un-retired rel ids, new optional columns) do not move the version.
