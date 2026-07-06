cmake_minimum_required (VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# DuckDB v1.5.4 amalgamation (https://github.com/duckdb/duckdb, MIT).
# Used by the Speckle 4.0 artefact send pipeline to write the Zstd-parquet
# bundle (the parquet extension + zstd are statically included in the
# amalgamation). Consumed through the C API (duckdb.h) only, so the add-on's
# /Zc:wchar_t- and iterator-debug-level settings never cross the ABI.
add_library(duckdb STATIC src/duckdb.cpp)
target_include_directories(duckdb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    # /bigobj: the amalgamation exceeds the default COFF section limit.
    # /GL-: opt out of the project-wide LTCG (link times on a 25MB TU are prohibitive).
    # /EHsc: DuckDB requires exception semantics.
    target_compile_options(duckdb PRIVATE /bigobj /GL- /EHsc /wd4244 /wd4267 /wd4996)
    # Match the add-on's _ITERATOR_DEBUG_LEVEL=0 so Debug-config links are consistent.
    # WIN32_LEAN_AND_MEAN keeps combaseapi.h's `#define interface struct` out of
    # windows.h (DuckDB has fields literally named `interface`); NOMINMAX likewise.
    target_compile_definitions(duckdb PRIVATE _ITERATOR_DEBUG_LEVEL=0 WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

target_compile_definitions(duckdb PRIVATE DUCKDB_BUILD_LIBRARY)
# Static lib: no dllexport/dllimport on the C API — PUBLIC so consumers of
# duckdb.h see plain (statically-linkable) declarations too.
target_compile_definitions(duckdb PUBLIC DUCKDB_STATIC_BUILD)

if(WIN32)
    # DuckDB's file-lock diagnostics call the Windows Restart Manager (RmStartSession & co).
    target_link_libraries(duckdb INTERFACE rstrtmgr)
endif()

# DuckDB targets C++17; the repo-wide CMAKE_CXX_STANDARD 20 breaks it
# (std::uncaught_exception removal + stricter parsing). Pin the lib to 17 —
# only the C API crosses into the C++20 add-on, so the standards never mix.
set_target_properties(duckdb PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
