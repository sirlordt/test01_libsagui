cmake_minimum_required(VERSION 3.22)

project( TEST01_LIBSAGUI VERSION 1.0.0 LANGUAGES C CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

set( CMAKE_FIND_LIBRARY_SUFFIXES ".a" )
set( BUILD_SHARED_LIBS OFF )
set( CMAKE_EXE_LINKER_FLAGS "-static" )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin )

add_subdirectory( ${PROJECT_SOURCE_DIR}/src )

add_subdirectory( ${PROJECT_SOURCE_DIR}/external/libraries )  # look in hello subdirectory for CMakeLists.txt to process
