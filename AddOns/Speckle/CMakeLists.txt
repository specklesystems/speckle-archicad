cmake_minimum_required (VERSION 3.16)

set(SPECKLE_ADDON_LIB SpeckleAddOn)
set(SPECKLE_ADDON_RESOURCES SpeckleAddOnResources)

function (SetCompilerOptions target)
	target_compile_features (${target} PUBLIC cxx_std_14)
	target_compile_options (${target} PUBLIC "$<$<CONFIG:Debug>:-DDEBUG>")
	if (WIN32)
		target_compile_options (${target} PUBLIC /W4
			/Zc:wchar_t-
			/wd4499
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
endfunction ()

set_property (GLOBAL PROPERTY USE_FOLDERS ON)

set (CMAKE_SUPPRESS_REGENERATION 1)
set (CMAKE_CONFIGURATION_TYPES Debug;Release;RelWithDebInfo)
set (SPECKLE_ADDON_NAME "Speckle")

if (WIN32)
	add_definitions (-DUNICODE -D_UNICODE)
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
		COMMAND python "${AddOnResourcesFolderAbsolute}/Tools/CompileResources.py" "${AC_ADDON_LANGUAGE}" "${AC_API_DEVKIT_DIR}" "${AddOnSourcesFolderAbsolute}" "${AddOnResourcesFolderAbsolute}" "${ResourceObjectsDir}" "${ResourceObjectsDir}/${SPECKLE_ADDON_NAME}.res"
		COMMAND ${CMAKE_COMMAND} -E touch "${ResourceObjectsDir}/AddOnResources.stamp"
	)
else ()
	add_custom_command (
		OUTPUT "${ResourceObjectsDir}/AddOnResources.stamp"
		DEPENDS ${AddOnResourceFiles} ${AddOnImageFiles}
		COMMENT "Compiling resources..."
		COMMAND ${CMAKE_COMMAND} -E make_directory "${ResourceObjectsDir}"
		COMMAND python "${AddOnResourcesFolderAbsolute}/Tools/CompileResources.py" "${AC_ADDON_LANGUAGE}" "${AC_API_DEVKIT_DIR}" "${AddOnSourcesFolderAbsolute}" "${AddOnResourcesFolderAbsolute}" "${ResourceObjectsDir}" "${CMAKE_BINARY_DIR}/$<CONFIG>/${SPECKLE_ADDON_NAME}.bundle/Contents/Resources"
		COMMAND ${CMAKE_COMMAND} -E copy "${AC_API_DEVKIT_DIR}/Support/Inc/PkgInfo" "${CMAKE_BINARY_DIR}/$<CONFIG>/${SPECKLE_ADDON_NAME}.bundle/Contents/PkgInfo"
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
		${UtilsFiles})
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
		${UtilsFiles})
endif ()

set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES OUTPUT_NAME ${SPECKLE_ADDON_NAME})
if (WIN32)
	set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES SUFFIX ".apx")
else ()
	set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES BUNDLE TRUE)
	set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_LIST_DIR}/${AddOnResourcesFolder}/RFIX.mac/Info.plist")
	set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${AC_ADDON_LANGUAGE}/$<CONFIG>")
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
		${AC_API_DEVKIT_DIR}/Support/Inc
		${LIB_INCLUDE_DIRS}
)

if (WIN32)
	target_link_libraries (${SPECKLE_ADDON_LIB}
		"$<$<CONFIG:Debug>:${AC_API_DEVKIT_DIR}/Support/Lib/Win/ACAP_STATD.lib>"
		"$<$<CONFIG:Release>:${AC_API_DEVKIT_DIR}/Support/Lib/Win/ACAP_STAT.lib>"
		"$<$<CONFIG:RelWithDebInfo>:${AC_API_DEVKIT_DIR}/Support/Lib/Win/ACAP_STAT.lib>"
	)
else ()
	find_library (CocoaFramework Cocoa)
	target_link_libraries (${SPECKLE_ADDON_LIB}
		"${AC_API_DEVKIT_DIR}/Support/Lib/Mactel/libACAP_STAT.a"
		${CocoaFramework}
	)
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

set_target_properties (${SPECKLE_ADDON_LIB} PROPERTIES VS_DEBUGGER_COMMAND "C:\\Program Files\\GRAPHISOFT\\Archicad 27\\Archicad.exe")

# other libs
target_link_libraries(${SPECKLE_ADDON_LIB} json sqlite)

#compile definitions
SetCompilerParams(${SPECKLE_ADDON_LIB})
