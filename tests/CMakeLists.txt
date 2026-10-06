cmake_minimum_required(VERSION 3.16)
project(ElementTypeTests LANGUAGES CXX)

set(ARCHICAD_VERSION 29 CACHE STRING "Archicad SDK version to test")
if(NOT ARCHICAD_VERSION MATCHES "^(27|28|29)$")
    message(FATAL_ERROR "ARCHICAD_VERSION must be 27, 28 or 29")
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
get_filename_component(REPO ".." ABSOLUTE BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SDK "${REPO}/Libs/acapi${ARCHICAD_VERSION}")
file(GLOB MODULES "${SDK}/Support/Modules/*")

add_executable(ElementTypeTests
    ElementTypeTests.cpp
    "${REPO}/AddOns/Speckle/Sources/AddOn/Converter/ElementTypeToStringConverter.cpp")
target_include_directories(ElementTypeTests PRIVATE
    "${REPO}/AddOns/Speckle/Sources/AddOn/Converter"
    "${SDK}/Support/Inc" ${MODULES})
target_compile_definitions(ElementTypeTests PRIVATE
    AC${ARCHICAD_VERSION} MEPAPI_COMPILE ACExtension UNICODE _UNICODE _ITERATOR_DEBUG_LEVEL=0)
target_compile_options(ElementTypeTests PRIVATE /Zc:wchar_t- /wd4996 /wd4499)
target_link_libraries(ElementTypeTests PRIVATE "${SDK}/Support/Modules/GSRoot/Win/GSRootImp.LIB")

# ENG-10286: MEPAPI requires the Archicad host; unique test IDs isolate the naming policy.
file(STRINGS "${SDK}/Support/Modules/MEPAPI/ACAPI/MEPAdapter.hpp"
    DECLARATIONS REGEX "extern const API_Guid")
set(DOUBLES "#include \"ACAPI/MEPAdapter.hpp\"\nnamespace ACAPI::MEP {\n")
set(INDEX 0)
foreach(DECLARATION IN LISTS DECLARATIONS)
    string(REGEX MATCH "API_Guid ([A-Za-z0-9_]+)" MATCH "${DECLARATION}")
    math(EXPR INDEX "${INDEX} + 1")
    string(APPEND DOUBLES "const API_Guid ${CMAKE_MATCH_1} = {${INDEX}};\n")
endforeach()
string(APPEND DOUBLES "}\n")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/MepClassIds.cpp" "${DOUBLES}")
target_sources(ElementTypeTests PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/MepClassIds.cpp")

enable_testing()
add_test(NAME ElementTypeNames COMMAND ElementTypeTests)

add_executable(IngestionProgressTests
    IngestionProgressTests.cpp
    "${REPO}/AddOns/Speckle/Sources/AddOn/Artifacts/ArtifactUploader.cpp")
target_include_directories(IngestionProgressTests PRIVATE
    "${REPO}/AddOns/Speckle/Sources/AddOn/Artifacts"
    "${REPO}/AddOns/Speckle/Sources/AddOn/Converter"
    "${REPO}/AddOns/Speckle/Sources/AddOn/Network"
    "${REPO}/AddOns/Speckle/Sources/AddOn/Connector"
    "${REPO}/AddOns/Speckle/Sources/AddOn/Utils"
    "${REPO}/Libs/json/include")
add_test(NAME IngestionProgress COMMAND IngestionProgressTests)
