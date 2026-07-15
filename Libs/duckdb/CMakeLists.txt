cmake_minimum_required (VERSION 3.16)

# DuckDB v1.5.4 — OFFICIAL PREBUILT BINARY (MIT), from
# https://github.com/duckdb/duckdb/releases/download/v1.5.4/libduckdb-windows-amd64.zip
# (duckdb.h + duckdb.lib import lib + duckdb.dll; the DLL lives in redist/
# rather than bin/ because the repo's .gitignore excludes **/bin).
#
# Used by the Speckle 4.0 artefact send pipeline to write the Zstd-parquet
# bundle. The official DLL ships with the parquet extension statically linked
# (the source amalgamation does NOT — its extension loader is a no-op stub,
# which is why an earlier iteration vendored the whole source tree).
#
# Consumed through the C API only (duckdb.h): a stable C ABI, so one release
# DLL serves every toolset/configuration and the add-on's /Zc:wchar_t- and
# iterator-debug-level settings never cross the boundary.
#
# The DLL is DELAY-LOADED by the add-on and LoadLibrary'd by full path from
# the add-on's own folder at first use (Windows resolves plugin dependencies
# against Archicad.exe's folder, not the .apx folder — same pattern the .NET
# connectors use for nironcompress.dll). A post-build step on the add-on
# copies it next to the .apx.
#
# To upgrade: replace include/duckdb.h, lib/duckdb.lib, bin/duckdb.dll with a
# newer official release. Keep BundleWriter's COPY options compatible
# (DICTIONARY_SIZE_LIMIT requires >= 1.2).

if (WIN32)
    add_library(duckdb SHARED IMPORTED GLOBAL)
    set_target_properties(duckdb PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/redist/duckdb.dll
        IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/duckdb.lib
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)
else ()
    if (APPLE)
        set(SPECKLE_DUCKDB_ROOT "$ENV{SPECKLE_DUCKDB_ROOT}" CACHE PATH "Directory containing the official DuckDB macOS dylib")
        if (SPECKLE_DUCKDB_ROOT)
            set(DUCKDB_DYLIB "${SPECKLE_DUCKDB_ROOT}/libduckdb.dylib")
        else ()
            include(FetchContent)
            FetchContent_Declare(
                duckdb_prebuilt
                URL https://github.com/duckdb/duckdb/releases/download/v1.5.4/libduckdb-osx-universal.zip
                URL_HASH SHA256=3f3c52970ad1407ec5037062e1a5e575b24bd5b993c889f89fe5876eff47782c
                DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
            FetchContent_MakeAvailable(duckdb_prebuilt)
            set(DUCKDB_DYLIB "${duckdb_prebuilt_SOURCE_DIR}/libduckdb.dylib")
        endif ()

        if (NOT EXISTS "${DUCKDB_DYLIB}")
            message(FATAL_ERROR "DuckDB macOS library was not found at ${DUCKDB_DYLIB}")
        endif ()

        add_library(duckdb SHARED IMPORTED GLOBAL)
        set_target_properties(duckdb PROPERTIES
            IMPORTED_LOCATION "${DUCKDB_DYLIB}"
            INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")
    else ()
        add_library(duckdb INTERFACE)
        target_include_directories(duckdb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    endif ()
endif ()
