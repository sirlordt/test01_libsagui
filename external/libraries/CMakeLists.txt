# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required( VERSION 3.11 )

project( MAIN_EXTERNAL_LIBRARIES
         VERSION 0.1
         DESCRIPTION "Main External Libraries" )

# ******* libsagui ********
add_subdirectory( ${PROJECT_SOURCE_DIR}/libsagui )  # look in libsagui subdirectory for CMakeLists.txt to process
# ******* libsagui ********
