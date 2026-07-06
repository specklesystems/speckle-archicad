cmake_minimum_required (VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# DuckDB v1.5.4 (https://github.com/duckdb/duckdb, MIT) with the PARQUET
# EXTENSION STATICALLY LINKED. Generated from the DuckDB source tree with the
# official packaging script:
#   python -c "import sys; sys.path.append('scripts'); import package_build;
#              package_build.build_package('<out>', ['parquet'], False)"
# (same mechanism duckdb-node uses). The plain released amalgamation does NOT
# contain the parquet extension — its extension loader is a no-op stub — so
# COPY ... (FORMAT PARQUET) would fail at runtime. The generated
# generated_extension_loader_package_build.cpp provides the real
# ExtensionHelper::LoadAllExtensions that registers ParquetExtension at
# duckdb_open time.
#
# Used by the Speckle 4.0 artefact send pipeline to write the Zstd-parquet
# bundle. Consumed through the C API (duckdb.h) only, so the add-on's
# /Zc:wchar_t- and iterator-debug-level settings never cross the ABI.

# The exact compile list (unity ub_*.cpp files + standalone sources +
# third_party + the generated loader) as returned by build_package —
# see sources.cmake, generated alongside the tree. Do not glob: several
# vendored files (e.g. utf8proc_data.cpp) are #include'd data, not TUs.
include(${CMAKE_CURRENT_SOURCE_DIR}/sources.cmake)
list(TRANSFORM DUCKDB_ALL_SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_library(duckdb STATIC ${DUCKDB_ALL_SOURCES})

# Public: consumers include duckdb.h from src/include.
target_include_directories(duckdb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# Private: the package root (ub files include "src/..."), the extension, and
# the third-party include dirs (list from package_build.third_party_includes()).
target_include_directories(duckdb PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/extension/parquet/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/concurrentqueue
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fast_float
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fastpforlib
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fmt/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/fsst
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/httplib
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/hyperloglog
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/jaro_winkler
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/jaro_winkler/details
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libpg_query
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libpg_query/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lz4
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/brotli/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/brotli/common
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/brotli/dec
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/brotli/enc
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mbedtls/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mbedtls/library
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/miniz
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/pcg
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/pdqsort
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/re2
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ska_sort
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/skiplist
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/tdigest
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utf8proc
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/utf8proc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/vergesort
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/yyjson/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/zstd/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/parquet
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/snappy
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/thrift)

if(MSVC)
    # /bigobj: several unity TUs exceed the default COFF section limit.
    # /GL-: opt out of the project-wide LTCG (link times would be prohibitive).
    # /EHsc: DuckDB requires exception semantics.
    target_compile_options(duckdb PRIVATE /bigobj /GL- /EHsc /wd4244 /wd4267 /wd4996)
    # Match the add-on's _ITERATOR_DEBUG_LEVEL=0 so Debug-config links are consistent.
    # WIN32_LEAN_AND_MEAN keeps combaseapi.h's `#define interface struct` out of
    # windows.h (DuckDB has fields literally named `interface`); NOMINMAX likewise.
    target_compile_definitions(duckdb PRIVATE _ITERATOR_DEBUG_LEVEL=0 WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

target_compile_definitions(duckdb PRIVATE
    DUCKDB_BUILD_LIBRARY
    DUCKDB_EXTENSION_PARQUET_LINKED=1
    DUCKDB_EXTENSION_AUTOLOAD_DEFAULT=0
    DUCKDB_EXTENSION_AUTOINSTALL_DEFAULT=0)
# Static lib: no dllexport/dllimport on the C API — PUBLIC so consumers of
# duckdb.h see plain (statically-linkable) declarations too.
target_compile_definitions(duckdb PUBLIC DUCKDB_STATIC_BUILD)

if(WIN32)
    # DuckDB's file-lock diagnostics call the Windows Restart Manager (RmStartSession & co).
    target_link_libraries(duckdb INTERFACE rstrtmgr ws2_32)
endif()

# DuckDB targets C++17; the repo-wide CMAKE_CXX_STANDARD 20 breaks it
# (std::uncaught_exception removal + stricter parsing). Pin the lib to 17 —
# only the C API crosses into the C++20 add-on, so the standards never mix.
set_target_properties(duckdb PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
