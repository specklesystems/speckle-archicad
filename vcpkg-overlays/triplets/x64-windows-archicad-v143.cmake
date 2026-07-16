# Triplet for the Archicad add-on's Arrow/Parquet dependency (AC29, toolset v143).
# Identical ABI to the v142 triplet (see x64-windows-archicad-v142.cmake for the rationale);
# only the platform toolset differs. Arrow SIMD is disabled in the overlay port for both
# toolsets so AC 27/28/29 decode Parquet identically.
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_BUILD_TYPE release)
set(VCPKG_PLATFORM_TOOLSET v143)

set(VCPKG_CXX_FLAGS "/Zc:wchar_t- /D_ITERATOR_DEBUG_LEVEL=0 /D_HAS_AUTO_PTR_ETC=1")
set(VCPKG_C_FLAGS "/D_ITERATOR_DEBUG_LEVEL=0")
