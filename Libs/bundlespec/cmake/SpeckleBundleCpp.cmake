# SpeckleBundleCpp.cmake — usage-requirement targets for the shared bundle C++ package.
#
# Include from a consumer after setting BUNDLE_SPEC to this repo's root (a checkout or
# an extracted published bundle-spec-cpp-<x>.tar.gz):
#
#   set(BUNDLE_SPEC "/path/to/speckle-bundle-spec")
#   include(${BUNDLE_SPEC}/cmake/SpeckleBundleCpp.cmake)
#   target_link_libraries(mytarget PRIVATE speckle::bundle_writer)
#
# Targets (header-only; INTERFACE include dirs):
#   speckle::bundle_core    cpp/core — pure std C++17, no third-party deps
#   speckle::bundle_writer  cpp/writer + generated/cpp — REQUIRES Arrow+Parquet to compile
#   speckle::bundle_reader  cpp/reader + generated/cpp — REQUIRES Arrow+Parquet to compile
#
# Arrow is deliberately NOT resolved here: each consumer supplies its own
# (converters: apt-pinned shared libs; archicad: vendored static libs). Link your
# Arrow/Parquet libraries on the same target that links bundle_writer/bundle_reader.
#
# Pin guard: when the consumer sets -DBUNDLE_SPEC_EXPECT_VERSION=<x>, the include of
# AssertBundleSpecPin below fails the configure unless BUNDLE_SPEC points at the
# matching PUBLISHED artifact (a bare checkout has no bundle_spec_version.h).

if(TARGET speckle::bundle_core)
  return()  # already included
endif()

get_filename_component(_SBC_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(BUNDLE_SPEC_INCLUDE "${_SBC_ROOT}/generated/cpp")
include("${CMAKE_CURRENT_LIST_DIR}/AssertBundleSpecPin.cmake")

add_library(speckle_bundle_core INTERFACE)
target_include_directories(speckle_bundle_core INTERFACE "${_SBC_ROOT}/cpp/core")
add_library(speckle::bundle_core ALIAS speckle_bundle_core)

add_library(speckle_bundle_writer INTERFACE)
target_include_directories(speckle_bundle_writer INTERFACE
    "${_SBC_ROOT}/cpp/writer"
    "${_SBC_ROOT}/generated/cpp")
target_link_libraries(speckle_bundle_writer INTERFACE speckle_bundle_core)
add_library(speckle::bundle_writer ALIAS speckle_bundle_writer)

add_library(speckle_bundle_reader INTERFACE)
target_include_directories(speckle_bundle_reader INTERFACE
    "${_SBC_ROOT}/cpp/reader"
    "${_SBC_ROOT}/generated/cpp")
target_link_libraries(speckle_bundle_reader INTERFACE speckle_bundle_core)
add_library(speckle::bundle_reader ALIAS speckle_bundle_reader)
