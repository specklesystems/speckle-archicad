cmake_minimum_required (VERSION 3.16)

set(SPECKLE_ADDON_LIB SpeckleAddOn)
set(SPECKLE_ADDON_RESOURCES SpeckleAddOnResources)

function (SetCompilerOptions target)
	target_compile_features (${target} PUBLIC cxx_std_20)
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
endfunction ()

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_SUPPRESS_REGENERATION 1)
set (CMAKE_CONFIGURATION_TYPES Debug;Release;RelWithDebInfo)
set (SPECKLE_ADDON_NAME "Speckle")

if (APPLE)
	set(SPECKLE_ADDON_VERSION "1.0.0" CACHE STRING "Speckle add-on semantic version")
	file(READ
		"${AC_API_DEVKIT_DIR}/Support/Frameworks/GSRoot.framework/Versions/A/Resources/Info.plist"
		GSROOT_INFO_PLIST)
	string(REGEX MATCH "GSBuildNum[^0-9]+([0-9]+)" _ "${GSROOT_INFO_PLIST}")
	set(AC_DEVKIT_BUILD_NUMBER "${CMAKE_MATCH_1}")
	if (NOT AC_DEVKIT_BUILD_NUMBER)
		message(FATAL_ERROR "Could not read the Archicad DevKit build number")
	endif ()
	math(EXPR AC_COMPATIBILITY_VERSION "${ARCHICAD_VERSION} * 100000 + ${AC_DEVKIT_BUILD_NUMBER}")
	set(SPECKLE_BUNDLE_VERSION "${SPECKLE_ADDON_VERSION}.${AC_COMPATIBILITY_VERSION}")
	set(SPECKLE_INFO_PLIST "${CMAKE_CURRENT_BINARY_DIR}/SpeckleInfo.plist")
	configure_file(
		"${CMAKE_CURRENT_LIST_DIR}/Sources/AddOnResources/RFIX.mac/Info.plist"
		"${SPECKLE_INFO_PLIST}"
		@ONLY)
endif ()

if (WIN32)
	add_definitions (-DUNICODE -D_UNICODE -D_ITERATOR_DEBUG_LEVEL=0)
else ()
	add_definitions (-Dmacintosh=1)
endif ()
add_definitions (-DACExtension)

project (${SPECKLE_ADDON_NAME})

set (AddOnSourcesFolder Sources/AddOn)
set (AddOnResourcesFolder Sources/AddOnResources)

# AddOnResources
set (ResourceObjectsDir ${CMAKE_BINARY_DIR}/AddOns/${SPECKLE_ADDON_NAME}/ResourceObjects)

configure_file (${AddOnResourcesFolder}/ResourceMDIDIds.hpp.in ${ResourceObjectsDir}/ResourceMDIDIds.hpp)

file (GLOB AddOnImageFiles
	${AddOnResourcesFolder}/RFIX/Images/*.svg
)
if (WIN32)
	file (GLOB AddOnResourceFiles
		${AddOnResourcesFolder}/R${AC_ADDON_LANGUAGE}/*.grc
		${AddOnResourcesFolder}/RFIX/*.grc
		${AddOnResourcesFolder}/RFIX.win/*.rc2
		${AddOnResourcesFolder}/Tools/*.py
	)
else ()
	file (GLOB AddOnResourceFiles
		${AddOnResourcesFolder}/R${AC_ADDON_LANGUAGE}/*.grc
		${AddOnResourcesFolder}/RFIX/*.grc
		${AddOnResourcesFolder}/RFIX.mac/*.plist
		${AddOnResourcesFolder}/Tools/*.py
	)
endif ()

source_group ("Images" FILES ${AddOnImageFiles})
source_group ("Resources" FILES ${AddOnResourceFiles})
add_custom_target (
	${SPECKLE_ADDON_RESOURCES} ALL
	DEPENDS "${ResourceObjectsDir}/AddOnResources.stamp"
		Sources ${AddOnResourceFiles} ${AddOnImageFiles}
)

get_filename_component (AddOnSourcesFolderAbsolute "${CMAKE_CURRENT_LIST_DIR}/${AddOnSourcesFolder}" ABSOLUTE)
get_filename_component (AddOnResourcesFolderAbsolute "${CMAKE_CURRENT_LIST_DIR}/${AddOnResourcesFolder}" ABSOLUTE)

# Recursively create source groups for all files in AddOnSourcesFolder
function(create_source_groups base_path group_prefix)
	file(GLOB_RECURSE all_files CONFIGURE_DEPENDS "${base_path}/*")
	foreach(file ${all_files})
		# Get relative path and convert '/' to '\\' for Windows
		file(RELATIVE_PATH relative_path "${base_path}" "${file}")
		string(REPLACE "/" "\\" group_name "${group_prefix}/${relative_path}")
		# Get directory of the relative path
		get_filename_component(folder "${group_name}" PATH)
		source_group("${folder}" FILES "${file}")
	endforeach()
endfunction()

# Call function to create source groups
create_source_groups("${AddOnSourcesFolderAbsolute}" "Sources")

if (WIN32)
	add_custom_command (
		OUTPUT "${ResourceObjectsDir}/AddOnResources.stamp"
		DEPENDS ${AddOnResourceFiles} ${AddOnImageFiles}
		COMMENT "Compiling resources..."
		COMMAND ${CMAKE_COMMAND} -E make_directory "${ResourceObjectsDir}"
		COMMAND "${Python3_EXECUTABLE}" "${AddOnResourcesFolderAbsolute}/Tools/CompileResources.py" "${AC_ADDON_LANGUAGE}" "${AC_API_DEVKIT_DIR}" "${AddOnSourcesFolderAbsolute}" "${AddOnResourcesFolderAbsolute}" "${ResourceObjectsDir}" "${ResourceObjectsDir}/${SPECKLE_ADDON_NAME}.res"
		COMMAND ${CMAKE_COMMAND} -E touch "${ResourceObjectsDir}/AddOnResources.stamp"
	)
else ()
	add_custom_command (
		OUTPUT "${ResourceObjectsDir}/AddOnResources.stamp"
		DEPENDS ${AddOnResourceFiles} ${AddOnImageFiles}
		COMMENT "Compiling resources..."
		COMMAND ${CMAKE_COMMAND} -E make_directory "${ResourceObjectsDir}"
		COMMAND "${Python3_EXECUTABLE}" "${AddOnResourcesFolderAbsolute}/Tools/CompileResources.py" "${AC_ADDON_LANGUAGE}" "${AC_API_DEVKIT_DIR}" "${AddOnSourcesFolderAbsolute}" "${AddOnResourcesFolderAbsolute}" "${ResourceObjectsDir}" "${CMAKE_BINARY_DIR}/${AC_ADDON_LANGUAGE}/$<CONFIG>/${SPECKLE_ADDON_NAME}.bundle/Contents/Resources"
		COMMAND ${CMAKE_COMMAND} -E copy "${AC_API_DEVKIT_DIR}/Support/Inc/PkgInfo" "${CMAKE_BINARY_DIR}/${AC_ADDON_LANGUAGE}/$<CONFIG>/${SPECKLE_ADDON_NAME}.bundle/Contents/PkgInfo"
		COMMAND ${CMAKE_COMMAND} -E touch "${ResourceObjectsDir}/AddOnResources.stamp"
	)
endif ()

# AddOn
file (GLOB AddOnHeaderFiles
	${AddOnSourcesFolder}/*.h
	${AddOnSourcesFolder}/*.hpp
)
file (GLOB AddOnSourceFiles
	${AddOnSourcesFolder}/*.c
	${AddOnSourcesFolder}/*.cpp
	${AddOnSourcesFolder}/*.cc
)
set (
	AddOnFiles
	${AddOnHeaderFiles}
	${AddOnSourceFiles})
source_group ("AddOnMain" FILES ${AddOnFiles})

# file org
set (BrowserFolder Sources/AddOn/Browser)
file (GLOB BrowserFiles ${BrowserFolder}/*.h ${BrowserFolder}/*.cpp)
source_group ("Browser" FILES ${BrowserFiles})

set (ConnectorFolder Sources/AddOn/Connector)
file (GLOB ConnectorFiles ${ConnectorFolder}/*.h ${ConnectorFolder}/*.cpp)
source_group ("Connector" FILES ${ConnectorFiles})

set (BridgesFolder Sources/AddOn/Connector/Bridges)
file (GLOB BridgesFiles ${BridgesFolder}/*.h ${BridgesFolder}/*.cpp)
source_group ("Connector/Bridges" FILES ${BridgesFiles})

set (ConverterFolder Sources/AddOn/Converter)
file (GLOB ConverterFiles ${ConverterFolder}/*.h ${ConverterFolder}/*.cpp)
source_group ("Converter" FILES ${ConverterFiles})

set (SpeckleToHostFolder Sources/AddOn/Converter/SpeckleToHost)
file (GLOB SpeckleToHostFiles ${SpeckleToHostFolder}/*.h ${SpeckleToHostFolder}/*.cpp)
source_group ("Converter/SpeckleToHost" FILES ${SpeckleToHostFiles})

set (HostToSpeckleFolder Sources/AddOn/Converter/HostToSpeckle)
file (GLOB HostToSpeckleFiles ${HostToSpeckleFolder}/*.h ${HostToSpeckleFolder}/*.cpp)
source_group ("Converter/HostToSpeckle" FILES ${HostToSpeckleFiles})

set (DataTypesFolder Sources/AddOn/DataTypes)
file (GLOB DataTypesFiles ${DataTypesFolder}/*.h ${DataTypesFolder}/*.cpp)
source_group ("DataTypes" FILES ${DataTypesFiles})

set (StorageFolder Sources/AddOn/Storage)
file (GLOB StorageFiles ${StorageFolder}/*.h ${StorageFolder}/*.cpp)
source_group ("Storage" FILES ${StorageFiles})

set (UtilsFolder Sources/AddOn/Utils)
file (GLOB UtilsFiles ${UtilsFolder}/*.h ${UtilsFolder}/*.cpp)
source_group ("Utils" FILES ${UtilsFiles})

set (ArtifactsFolder Sources/AddOn/Artifacts)
file (GLOB ArtifactsFiles ${ArtifactsFolder}/*.h ${ArtifactsFolder}/*.cpp)
source_group ("Artifacts" FILES ${ArtifactsFiles})

set (NetworkFolder Sources/AddOn/Network)
file (GLOB NetworkFiles ${NetworkFolder}/*.h ${NetworkFolder}/*.cpp ${NetworkFolder}/*.mm)
source_group ("Network" FILES ${NetworkFiles})

set (DiagnosticsFolder Sources/AddOn/Diagnostics)
file (GLOB DiagnosticsFiles ${DiagnosticsFolder}/*.h ${DiagnosticsFolder}/*.cpp)
source_group ("Diagnostics" FILES ${DiagnosticsFiles})

if (WIN32)
	add_library (${SPECKLE_ADDON_LIB} SHARED
		${AddOnFiles}
		${BrowserFiles}
		${ConnectorFiles}
		${BridgesFiles}
		${ConverterFiles}
		${SpeckleToHostFiles}
		${HostToSpeckleFiles}
		${DataTypesFiles}
		${StorageFiles}
		${UtilsFiles}
		${ArtifactsFiles}
		${NetworkFiles}
		${DiagnosticsFiles})
else ()
	add_library (${SPECKLE_ADDON_LIB} MODULE
		${AddOnFiles}
		${BrowserFiles}
		${ConnectorFiles}
		${BridgesFiles}
		${ConverterFiles}
		${SpeckleToHostFiles}
		${HostToSpeckleFiles}
		${DataTypesFiles}
		${StorageFiles}
		${UtilsFiles}
		${ArtifactsFiles}
		${NetworkFiles}
		${DiagnosticsFiles})
endif ()

set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES OUTPUT_NAME ${SPECKLE_ADDON_NAME})
if (WIN32)
	set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES SUFFIX ".apx")
else ()
	set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES
		BUNDLE TRUE
		BUNDLE_EXTENSION bundle
		MACOSX_BUNDLE_INFO_PLIST "${SPECKLE_INFO_PLIST}"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${AC_ADDON_LANGUAGE}/$<CONFIG>"
		BUILD_WITH_INSTALL_RPATH TRUE
		INSTALL_RPATH "@loader_path/../Frameworks;@executable_path/../Frameworks")
	set_property(TARGET ${SPECKLE_ADDON_LIB} APPEND PROPERTY LINK_DEPENDS "${SPECKLE_INFO_PLIST}")
	target_compile_options(${SPECKLE_ADDON_LIB} PRIVATE "$<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>")
endif ()

if (WIN32)
	target_link_options (${SPECKLE_ADDON_LIB} PUBLIC "${ResourceObjectsDir}/${SPECKLE_ADDON_NAME}.res")
	target_link_options (${SPECKLE_ADDON_LIB} PUBLIC /export:GetExportedFuncAddrs,@1 /export:SetImportedFuncAddrs,@2)
endif ()

target_include_directories (${SPECKLE_ADDON_LIB} PUBLIC
		${AddOnSourcesFolder}
		${BrowserFolder}
		${ConnectorFolder}
		${BridgesFolder}
		${ConverterFolder}
		${HostToSpeckleFolder}
		${SpeckleToHostFolder}
		${DataTypesFolder}
		${StorageFolder}
		${UtilsFolder}
		${ArtifactsFolder}
		${NetworkFolder}
		${DiagnosticsFolder}
		${AC_API_DEVKIT_DIR}/Support/Inc
		${LIB_INCLUDE_DIRS}
)

if (WIN32)
	target_link_libraries (${SPECKLE_ADDON_LIB}
		"${AC_API_DEVKIT_DIR}/Support/Lib/Win/ACAP_STAT.lib"
	)
else ()
	find_library (CocoaFramework Cocoa)
	find_library (FoundationFramework Foundation)
	target_link_libraries (${SPECKLE_ADDON_LIB}
		"${AC_API_DEVKIT_DIR}/Support/Lib/libACAP_STAT.a"
		${CocoaFramework}
		${FoundationFramework}
	)
	# The DevKit contains frameworks introduced by later Archicad maintenance
	# builds. Keep only dylibs that satisfy symbols the connector actually uses,
	# otherwise a build against the latest DevKit will not load in base releases.
	target_link_options(${SPECKLE_ADDON_LIB} PRIVATE "-Wl,-dead_strip_dylibs")
endif ()

SetCompilerOptions (${SPECKLE_ADDON_LIB})
set_source_files_properties (${AddOnSourceFiles} PROPERTIES LANGUAGE CXX)

file (GLOB ModuleFolders ${AC_API_DEVKIT_DIR}/Support/Modules/*)
target_include_directories (${SPECKLE_ADDON_LIB} PUBLIC ${ModuleFolders})
if (WIN32)
	file (GLOB LibFilesInFolder ${AC_API_DEVKIT_DIR}/Support/Modules/*/*/*.lib)
	target_link_libraries (${SPECKLE_ADDON_LIB} ${LibFilesInFolder})
else ()
	file (GLOB FrameworkFilesInFolder ${AC_API_DEVKIT_DIR}/Support/Frameworks/*.framework)
	target_link_libraries (${SPECKLE_ADDON_LIB} ${FrameworkFilesInFolder})
endif ()
add_dependencies (${SPECKLE_ADDON_LIB} ${SPECKLE_ADDON_RESOURCES})


# group to folder
set_target_properties(${SPECKLE_ADDON_RESOURCES} PROPERTIES FOLDER Resources)

set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES VS_DEBUGGER_COMMAND "C:\\Program Files\\GRAPHISOFT_INT\\Archicad 29\\Archicad.exe")

# other libs
target_link_libraries(${SPECKLE_ADDON_LIB} json spdlog sqlite sha md5 duckdb)
if (WIN32)
	target_link_libraries(${SPECKLE_ADDON_LIB} winhttp delayimp)
	# duckdb.dll is delay-loaded: Windows resolves plugin dependencies against
	# Archicad.exe's folder, not the .apx folder, so BundleWriter LoadLibrary's
	# it by full path from the add-on's own directory before first use.
	target_link_options(${SPECKLE_ADDON_LIB} PRIVATE /DELAYLOAD:duckdb.dll)
	# Ship the DLL next to the .apx (debugging + installer zip pick it up from there).
	add_custom_command(TARGET ${SPECKLE_ADDON_LIB} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${CMAKE_SOURCE_DIR}/Libs/duckdb/redist/duckdb.dll"
			"$<TARGET_FILE_DIR:${SPECKLE_ADDON_LIB}>")
else ()
	find_program(CODESIGN_EXECUTABLE codesign REQUIRED)
	set(DEFAULT_CODESIGN_IDENTITY "$ENV{SPECKLE_CODESIGN_IDENTITY}")
	if (NOT DEFAULT_CODESIGN_IDENTITY)
		set(DEFAULT_CODESIGN_IDENTITY "-")
	endif ()
	set(SPECKLE_CODESIGN_IDENTITY "${DEFAULT_CODESIGN_IDENTITY}" CACHE STRING "macOS code-signing identity; '-' creates a local ad-hoc signature")
	add_custom_command(TARGET ${SPECKLE_ADDON_LIB} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory
			"$<TARGET_BUNDLE_DIR:${SPECKLE_ADDON_LIB}>/Contents/Frameworks"
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"$<TARGET_FILE:duckdb>"
			"$<TARGET_BUNDLE_DIR:${SPECKLE_ADDON_LIB}>/Contents/Frameworks/libduckdb.dylib"
		COMMAND "${CODESIGN_EXECUTABLE}" --force --deep --sign "${SPECKLE_CODESIGN_IDENTITY}"
			"$<TARGET_BUNDLE_DIR:${SPECKLE_ADDON_LIB}>"
		COMMENT "Signing the Speckle macOS bundle")
endif ()

#compile definitions
SetCompilerParams(${SPECKLE_ADDON_LIB})
