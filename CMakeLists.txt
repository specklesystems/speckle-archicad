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

# Vendored minimal static Arrow (see Libs/arrow/ARROW_VERSION.txt): libs ship zipped,
# extracted here at configure time; the toolset picks the matching lib set.
if (WIN32)
	if (CMAKE_VS_PLATFORM_TOOLSET MATCHES "v142")
		set(ARROW_TOOLSET "v142")
	else ()
		set(ARROW_TOOLSET "v143")
	endif ()
	set(ARROW_LIB_DIR "${CMAKE_SOURCE_DIR}/Libs/arrow/${ARROW_TOOLSET}")
	if (NOT EXISTS "${ARROW_LIB_DIR}/arrow_static.lib" OR
	    "${CMAKE_SOURCE_DIR}/Libs/arrow/${ARROW_TOOLSET}.zip" IS_NEWER_THAN "${ARROW_LIB_DIR}/arrow_static.lib")
		message(STATUS "Extracting vendored Arrow libs (${ARROW_TOOLSET})")
		file(ARCHIVE_EXTRACT INPUT "${CMAKE_SOURCE_DIR}/Libs/arrow/${ARROW_TOOLSET}.zip" DESTINATION "${ARROW_LIB_DIR}")
	endif ()
endif ()

set(LIB_INCLUDE_DIRS
		${CMAKE_SOURCE_DIR}/Libs/json/include
		${CMAKE_SOURCE_DIR}/Libs/spdlog/include
		${CMAKE_SOURCE_DIR}/Libs/sqlite/include
		${CMAKE_SOURCE_DIR}/Libs/arrow/include
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
