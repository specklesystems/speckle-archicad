Vendored from speckle-bundle-spec (schema_version 5), generated/cpp/:
  envelope_spec.h — rel/node-kind vocabulary + catalog rows.
  bundle_cols.h   — named column indices per produced table (no arrow dependency).

bundle_cols.h declares camera_views::near/far, which windef.h defines as macros;
include it before <windows.h> or #undef them first (BundleWriter.cpp does the latter).

Pinned to spec commit 5e54be4efec17ae0e5d8b42e2be4ab7c1ccbccb6 (2026-08-06).

NOTE: the spec's package.json version (5.0.0) does NOT change on additive
vocabulary edits — rel types have been un-retired (IN_GROUP 17, HOSTED_ON 22,
IN_ASSEMBLY 18) without a version bump. Compare against the commit hash above,
not the version string, when checking whether this copy is stale.

Regenerate with 'npm run generate' in the spec repo and re-copy; do not edit by hand.
