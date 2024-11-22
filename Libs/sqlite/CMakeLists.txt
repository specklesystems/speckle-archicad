cmake_minimum_required (VERSION 3.16)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(include)
add_library(sqlite STATIC src/shell.c src/sqlite3.c)
target_include_directories(sqlite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


