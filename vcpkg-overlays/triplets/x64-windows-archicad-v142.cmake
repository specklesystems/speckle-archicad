# Triplet for the Archicad add-on's Arrow/Parquet dependency (AC27 + AC28, toolset v142).
#
# The add-on links Arrow statically INTO the .apx (single-file deployment), so Arrow and all
# its transitive deps must be built with the exact ABI the add-on uses (root CMakeLists.txt +
# AddOns/Speckle/CMakeLists.txt SetCompilerOptions):
#   static libs + dynamic CRT (/MD, CMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDLL, all configs)
#   /Zc:wchar_t-            (Archicad devkit forces wchar_t to a typedef, not a native type)
#   _ITERATOR_DEBUG_LEVEL=0 (add-on defines it unconditionally, all configs)
# A release-only build serves both Debug and Release add-on builds because the add-on always
# uses the release CRT (/MD) and IDL=0 — see build history (formerly Libs/arrow/build_arrow.ps1).
# _HAS_AUTO_PTR_ETC=1 restores C++17-removed STL bits (std::random_shuffle) some deps still use.
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_BUILD_TYPE release)
set(VCPKG_PLATFORM_TOOLSET v142)

set(VCPKG_CXX_FLAGS "/Zc:wchar_t- /D_ITERATOR_DEBUG_LEVEL=0 /D_HAS_AUTO_PTR_ETC=1")
set(VCPKG_C_FLAGS "/D_ITERATOR_DEBUG_LEVEL=0")
