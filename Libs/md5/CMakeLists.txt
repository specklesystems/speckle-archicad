cmake_minimum_required (VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(md5 STATIC src/md5.cpp)
target_include_directories(md5 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


