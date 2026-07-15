# AssertBundleSpecPin.cmake — shared by nwextract + rvextract.
#
# Opt-in guard that the C++ bundle-spec target is the expected PUBLISHED version, so
# it stays in lockstep with the specklepy Python target (both derive from one spec).
# Reads kSpecVersion from the published artifact's bundle_spec_version.h.
#
# Requires (set by the caller before include()):
#   BUNDLE_SPEC_INCLUDE          — the generated/cpp include dir
# Honours:
#   BUNDLE_SPEC_EXPECT_VERSION   — when set non-empty, the pin is enforced; else no-op.
#
# The unified-image build passes -DBUNDLE_SPEC_EXPECT_VERSION=<x> and points
# BUNDLE_SPEC at the extracted bundle-spec-cpp-<x>.tar.gz.

if(DEFINED BUNDLE_SPEC_EXPECT_VERSION AND NOT BUNDLE_SPEC_EXPECT_VERSION STREQUAL "")
  set(_bsp_vh "${BUNDLE_SPEC_INCLUDE}/bundle_spec_version.h")
  if(NOT EXISTS "${_bsp_vh}")
    message(FATAL_ERROR
      "bundle-spec pin: expected version ${BUNDLE_SPEC_EXPECT_VERSION} but ${_bsp_vh} is "
      "missing — point BUNDLE_SPEC at a PUBLISHED artifact (bundle-spec-cpp-<x>.tar.gz), "
      "not a bare generated/cpp checkout.")
  endif()
  file(READ "${_bsp_vh}" _bsp_vhc)
  string(REGEX MATCH "kSpecVersion[^\"]*\"([^\"]+)\"" _bsp_m "${_bsp_vhc}")
  if(NOT CMAKE_MATCH_1)
    message(FATAL_ERROR "bundle-spec pin: could not parse kSpecVersion from ${_bsp_vh}")
  endif()
  if(NOT CMAKE_MATCH_1 STREQUAL BUNDLE_SPEC_EXPECT_VERSION)
    message(FATAL_ERROR
      "bundle-spec pin MISMATCH: want ${BUNDLE_SPEC_EXPECT_VERSION}, artifact is ${CMAKE_MATCH_1}")
  endif()
  message(STATUS "bundle-spec pin OK: ${CMAKE_MATCH_1}")
endif()
