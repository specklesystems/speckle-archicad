cmake_minimum_required (VERSION 3.16)

project(archicad-speckle)

set(CMAKE_CXX_STANDARD 20)

# default CMAKE_BUILD_TYPE is RELEASE
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

enable_testing()

if(MSVC)
  # Enable Link Time Code Generation (LTGC) for the entire project
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /GL")
  set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} /LTCG")
  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /LTCG")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
  set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
endif()

set (AC_API_DEVKIT_DIR $ENV{AC_API_DEVKIT_DIR} CACHE PATH "API DevKit directory.")
set (ACAPINC_FILE_LOCATION ${AC_API_DEVKIT_DIR}/Support/Inc/ACAPinc.h)
if (EXISTS ${ACAPINC_FILE_LOCATION})
	file (READ ${ACAPINC_FILE_LOCATION} ACAPIncContent)
	string (REGEX MATCHALL "#define[ \t]+ServerMainVers_([0-9][0-9])" VersionList ${ACAPIncContent})
	set (ARCHICAD_VERSION ${CMAKE_MATCH_1})
	message (STATUS "Archicad Version: ${ARCHICAD_VERSION}")
else ()
	message (FATAL_ERROR "Failed to detect Archicad version, please check the value of the AC_API_DEVKIT_DIR variable.")
endif ()


function (SetCompilerParams target)
	target_compile_options (${target} PUBLIC "$<$<CONFIG:Debug>:-DDEBUG>")
	if (WIN32)
		target_compile_options (${target} PUBLIC /W3 /MP
			/Zc:wchar_t-
			/wd4499
			/wd4996 
			/wd5208
		)
	else ()
		target_compile_options (${target} PUBLIC -Wall -Wextra -fvisibility=hidden
			-Wno-multichar
			-Wno-ctor-dtor-privacy
			-Wno-invalid-offsetof
			-Wno-ignored-qualifiers
			-Wno-reorder
			-Wno-overloaded-virtual
			-Wno-unused-parameter
			-Wno-missing-field-initializers
			-Wno-unknown-pragmas
			-Wno-missing-braces
			-Wno-unused-private-field
			-Wno-return-std-move
			-Wno-unused-value
			-Wno-switch
			-Wno-deprecated
			-Wno-shorten-64-to-32)
	endif ()

	target_compile_definitions(${target} PUBLIC
		AC${ARCHICAD_VERSION}
	)
endfunction ()


# ── Speckle bundle format: shared spec/writer/reader package + static Arrow ──
# BUNDLE_SPEC follows the converters intake pattern: default = the vendored published
# artifact (bundle-spec-cpp-<x> extracted under Libs/bundlespec), overridable to a live
# spec-repo checkout for cross-repo development (-DBUNDLE_SPEC=C:/path/to/checkout).
# The pin assert fails configure on a version mismatch; pass -DBUNDLE_SPEC_EXPECT_VERSION=""
# when pointing at a bare checkout (which has no synthesized bundle_spec_version.h).
set(BUNDLE_SPEC "${CMAKE_SOURCE_DIR}/Libs/bundlespec" CACHE PATH "speckle-bundle-spec published artifact or checkout")
set(BUNDLE_SPEC_EXPECT_VERSION "5.0.0" CACHE STRING "expected bundle-spec pin (empty = skip assert)")
set(BUNDLE_SPEC_INCLUDE "${BUNDLE_SPEC}/generated/cpp")
include("${BUNDLE_SPEC}/cmake/AssertBundleSpecPin.cmake")

# Arrow/Parquet — fetched + built by vcpkg (manifest mode, vcpkg.json; overlay port + triplet
# under vcpkg-overlays/). No Arrow is vendored in-repo: the toolchain installs it at configure
# time and these CONFIG packages expose the static imported targets (Arrow::arrow_static,
# Parquet::parquet_static) with their include dirs + the whole static dep closure. Configure
# with -DCMAKE_TOOLCHAIN_FILE=<vcpkg>/scripts/buildsystems/vcpkg.cmake and
# -DVCPKG_TARGET_TRIPLET=x64-windows-archicad-v142|v143 (wired by ci-build, see build.ps1).
if (WIN32)
	find_package(Arrow CONFIG REQUIRED)
	find_package(Parquet CONFIG REQUIRED)
endif ()

set(LIB_INCLUDE_DIRS
		${CMAKE_SOURCE_DIR}/Libs/json/include
		${CMAKE_SOURCE_DIR}/Libs/spdlog/include
		${CMAKE_SOURCE_DIR}/Libs/sqlite/include
		${BUNDLE_SPEC_INCLUDE}
		${BUNDLE_SPEC}/cpp/core
		${BUNDLE_SPEC}/cpp/writer
		${BUNDLE_SPEC}/cpp/reader)
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${AC_ADDON_LANGUAGE}")

#Libs
add_subdirectory(Libs/json)
add_subdirectory(Libs/spdlog)
add_subdirectory(Libs/sqlite)

# AddOns
add_subdirectory(AddOns/Speckle)

set_target_properties(json spdlog sqlite PROPERTIES FOLDER Libs)
