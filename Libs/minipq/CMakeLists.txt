cmake_minimum_required (VERSION 3.16)

# minipq — dependency-free (zstd only) parquet writer + reader sized to the
# Speckle bundle subset. Header-only; see README.md for provenance.
add_library(minipq INTERFACE)
target_include_directories(minipq INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(minipq INTERFACE zstd)
