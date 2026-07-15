# Vendored speckle-bundle-spec artifact

This is the **published** `bundle-spec-cpp-<version>` artifact of
[speckle-bundle-spec](https://github.com/specklesystems/speckle-bundle-spec) —
the generated schema headers (`generated/cpp/`, incl. the synthesized
`bundle_spec_version.h` pin) plus the shared writer/reader C++ package
(`cpp/{core,writer,reader}`) and its CMake glue (`cmake/`).

Do not edit by hand. To bump: run `node codegen/publish.mjs` in the spec repo
(or download the release tarball) and replace this directory with the contents
of `dist/cpp/`. The build asserts the pin via `-DBUNDLE_SPEC_EXPECT_VERSION`
(root CMakeLists) — update that too when the version changes.

For live cross-repo development against a spec checkout instead:
`-DBUNDLE_SPEC=C:/path/to/speckle-bundle-spec -DBUNDLE_SPEC_EXPECT_VERSION=""`.
