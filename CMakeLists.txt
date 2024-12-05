cmake_minimum_required (VERSION 3.16)

project(archicad-speckle)

set(CMAKE_CXX_STANDARD 17)

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
		target_compile_options (${target} PUBLIC /W4 /WX /MP
			/Zc:wchar_t-
			/wd4499
			/wd5208
		)
	else ()
		target_compile_options (${target} PUBLIC -Wall -Wextra
			-fvisibility=hidden
			-Wno-multichar
			-Wno-ctor-dtor-privacy
			-Wno-invalid-offsetof
			-Wno-ignored-qualifiers
			-Wno-reorder
			-Wno-overloaded-virtual
			-Wno-unused-parameter
			-Wno-deprecated)
	endif ()

	target_compile_definitions(${target} PUBLIC
		AC${ARCHICAD_VERSION}
	)
endfunction ()


set(LIB_INCLUDE_DIRS 
		${CMAKE_SOURCE_DIR}/Libs/json/include
		${CMAKE_SOURCE_DIR}/Libs/spdlog/include
		${CMAKE_SOURCE_DIR}/Libs/sqlite/include
		${CMAKE_SOURCE_DIR}/Libs/sha/include)
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/${AC_ADDON_LANGUAGE}")

#Libs
add_subdirectory(Libs/json)
add_subdirectory(Libs/spdlog)
add_subdirectory(Libs/sqlite)
add_subdirectory(Libs/sha)

# AddOns
add_subdirectory(AddOns/Speckle)

set_target_properties(json spdlog sqlite sha PROPERTIES FOLDER Libs)
