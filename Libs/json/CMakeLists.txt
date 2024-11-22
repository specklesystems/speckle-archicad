cmake_minimum_required (VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(json STATIC src/json.cpp)
target_include_directories(json PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


