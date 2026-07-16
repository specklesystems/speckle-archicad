# vcpkg overlays for the Archicad add-on

Arrow/Parquet is fetched and built by **vcpkg** (manifest mode, `../vcpkg.json`) — the same
way the [speckle-converters](https://github.com/specklesystems/speckle-converters) native
extractors consume Arrow. Nothing Arrow-related is vendored into this repo anymore (no
headers, no prebuilt `.lib`s, no `build_arrow.ps1`); `find_package(Arrow CONFIG)` +
`find_package(Parquet CONFIG)` in the root `CMakeLists.txt` pull it from vcpkg.

The add-on links Arrow **statically into the `.apx`**, and it is loaded in-process by
Archicad, so its Arrow must match the add-on's exact ABI. Stock vcpkg triplets don't, so two
things here specialize the build:

## `triplets/x64-windows-archicad-v14x.cmake`

Extend the stock `x64-windows-static-md` model (static libs + `/MD`) with the add-on's ABI:
`/Zc:wchar_t-` (Archicad devkit forces a `wchar_t` typedef), `_ITERATOR_DEBUG_LEVEL=0`,
`_HAS_AUTO_PTR_ETC=1`, release-only, and the platform toolset — `v142` for AC27/28, `v143`
for AC29. These flags apply to Arrow **and** every transitive dep vcpkg builds, so the whole
static closure linked into the `.apx` is ABI-consistent.

## `ports/arrow/` (overlay port)

A copy of vcpkg's `arrow` port (baseline `f87344c`, Arrow 24.0.0#2) with two additions in
`portfile.cmake`:

- **SIMD off on x64** (`ARROW_SIMD_LEVEL=NONE`). Upstream only does this for arm64. v142
  cannot compile Arrow 24's constexpr SIMD bit-packing kernels, and keeping v143 scalar too
  makes AC 27/28/29 decode Parquet identically.
- **`decoder.cc` `static constexpr kBufferSize`** — a v142 constexpr-in-nested-lambda quirk;
  the promotion is a no-op on v143. Applied via `vcpkg_replace_string` (robust to line drift).

## Bumping Arrow

Change `version`/`builtin-baseline` in `../vcpkg.json`, then re-sync this overlay port from
the matching vcpkg commit and re-apply the two edits above. Keep the overlay in lockstep with
the version the converters use (shared `speckle-bundle-spec` writer targets that Arrow).
