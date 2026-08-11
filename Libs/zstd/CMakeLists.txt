cmake_minimum_required (VERSION 3.16)

# zstd 1.5.7 — vendored as the upstream single-file amalgamation
# (lib/build/single_file_libs/combine.py output), copied verbatim from
# specklesystems/speckle-converters (native/third_party/zstd, PR #15).
# Sole dependency of the minipq parquet writer/reader (Libs/minipq).
add_library(zstd STATIC zstd.c)
target_include_directories(zstd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
