# Triplet for the Archicad add-on's Arrow/Parquet dependency (AC27 + AC28, toolset v142).
#
# The add-on links Arrow statically INTO the .apx (single-file deployment), so Arrow and its
# static dep closure must share the add-on's CRT/STL ABI (root CMakeLists.txt +
# AddOns/Speckle/CMakeLists.txt): static libs + dynamic CRT (/MD, all configs) and
# _ITERATOR_DEBUG_LEVEL=0. A release-only build serves both Debug and Release add-on builds —
# the add-on always uses the release CRT (/MD) and IDL=0.
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_BUILD_TYPE release)
set(VCPKG_PLATFORM_TOOLSET v142)

# Release /MD already implies _ITERATOR_DEBUG_LEVEL=0; set it explicitly across the whole
# closure so every static lib linked into the .apx agrees on the STL container ABI.
set(VCPKG_CXX_FLAGS "/D_ITERATOR_DEBUG_LEVEL=0")
set(VCPKG_C_FLAGS "/D_ITERATOR_DEBUG_LEVEL=0")

# /Zc:wchar_t- is the Archicad devkit ABI (wchar_t as a typedef, not a native type). It is
# applied ONLY to the arrow port — i.e. Arrow + Parquet, whose headers the add-on compiles.
# It must NOT reach transitive deps: abseil (pulled via re2) has separate wchar_t vs
# unsigned-short str_format overloads that collapse into a redefinition and fail to compile
# under /Zc:wchar_t-. wchar_t never crosses Arrow's (char/std::string) public API, so the
# Arrow<->deps and Arrow<->add-on boundaries are both unaffected. _HAS_AUTO_PTR_ETC restores
# C++17-removed STL bits (std::random_shuffle) some Arrow sources still reference.
if(PORT STREQUAL "arrow")
    set(VCPKG_CXX_FLAGS "/Zc:wchar_t- /D_ITERATOR_DEBUG_LEVEL=0 /D_HAS_AUTO_PTR_ETC=1")
endif()
