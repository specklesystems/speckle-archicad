cmake_minimum_required (VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(sha STATIC src/picosha2.cpp)
target_include_directories(sha PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


