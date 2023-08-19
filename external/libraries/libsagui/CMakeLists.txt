cmake_minimum_required(VERSION 3.11-3.18)

project( LIBSAGUI )

# MAIN_ROOT_SOURCE_DIR come from the top most CMakeLists.txt file
#message(STATUS "CMAKE_SYSTEM_INCLUDE_PATH=${CMAKE_SYSTEM_INCLUDE_PATH}")

set( LIB_PROJECT_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/git_repo )
set( LIB_PROJECT_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/build )
set( LIB_PROJECT_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install )

message(STATUS "** ${CMAKE_PROJECT_NAME} ** LIB_PROJECT_SOURCE_DIR=${LIB_PROJECT_SOURCE_DIR}")
message(STATUS "** ${CMAKE_PROJECT_NAME} ** LIB_PROJECT_BUILD_DIR=${LIB_PROJECT_BUILD_DIR}")
message(STATUS "** ${CMAKE_PROJECT_NAME} ** LIB_PROJECT_INSTALL_DIR=${LIB_PROJECT_INSTALL_DIR}")

# Emulate the ExternalProject_Add but in config time.
# Because the Fetch_Declare, Fetch_Populate, Fetch_* no work. Never create the static libraries.
if ( NOT EXISTS "${LIB_PROJECT_BUILD_DIR}" OR
     NOT EXISTS "${LIB_PROJECT_INSTALL_DIR}" OR
     FORCE_BUILD_INSTALL_LIBSAGUI_LIBRARY )

  if ( NOT EXISTS "${LIB_PROJECT_SOURCE_DIR}/src/CMakeLists.txt" )

    execute_process( COMMAND git clone https://github.com/risoflora/libsagui ${LIB_PROJECT_SOURCE_DIR} )

  endif()

  file( MAKE_DIRECTORY "${LIB_PROJECT_BUILD_DIR}" )
  file( MAKE_DIRECTORY "${LIB_PROJECT_INSTALL_DIR}" )

  set(ENV{NO_COLOR} 1)
  execute_process( COMMAND cmake "${LIB_PROJECT_SOURCE_DIR}" -DCMAKE_COLOR_MAKEFILE:BOOL=OFF -DBUILD_SHARED_LIBS=OFF
                   WORKING_DIRECTORY "${LIB_PROJECT_BUILD_DIR}" )

  execute_process( COMMAND cmake --build "${LIB_PROJECT_BUILD_DIR}" )

  #cmake --install . --prefix ./install
  execute_process( COMMAND cmake --install "${LIB_PROJECT_BUILD_DIR}"
                                 --prefix "${LIB_PROJECT_INSTALL_DIR}" )

endif()

# Manual create the target to libhv
add_library( LIB_SAGUI_STATIC STATIC IMPORTED GLOBAL )
set_target_properties( LIB_SAGUI_STATIC PROPERTIES IMPORTED_LOCATION
                       ${LIB_PROJECT_INSTALL_DIR}/lib/libsagui.a )

target_include_directories( LIB_SAGUI_STATIC INTERFACE
                            ${LIB_PROJECT_INSTALL_DIR}/include )

add_library( LIB_MICRO_HTTPD_STATIC STATIC IMPORTED GLOBAL )
set_target_properties( LIB_MICRO_HTTPD_STATIC PROPERTIES IMPORTED_LOCATION
                       ${LIB_PROJECT_BUILD_DIR}/libmicrohttpd-0.9.76/lib/libmicrohttpd.a )

target_include_directories( LIB_MICRO_HTTPD_STATIC INTERFACE
                            ${LIB_PROJECT_BUILD_DIR}/libmicrohttpd-0.9.76/include )

add_library( LIB_PCRE2_STATIC STATIC IMPORTED GLOBAL )
set_target_properties( LIB_PCRE2_STATIC PROPERTIES IMPORTED_LOCATION
                       ${LIB_PROJECT_BUILD_DIR}/pcre2-10.42/lib/libpcre2-8.a )

target_include_directories( LIB_PCRE2_STATIC INTERFACE
                            ${LIB_PROJECT_BUILD_DIR}/pcre2-10.42/include )

add_library( LIB_Z_STATIC STATIC IMPORTED GLOBAL )
set_target_properties( LIB_Z_STATIC PROPERTIES IMPORTED_LOCATION
                       ${LIB_PROJECT_BUILD_DIR}/zlib-1.2.11/lib/libz.a )

target_include_directories( LIB_Z_STATIC INTERFACE
                            ${LIB_PROJECT_BUILD_DIR}/zlib-1.2.11/include )

target_link_libraries( LIB_SAGUI_STATIC INTERFACE LIB_MICRO_HTTPD_STATIC LIB_PCRE2_STATIC LIB_Z_STATIC )
