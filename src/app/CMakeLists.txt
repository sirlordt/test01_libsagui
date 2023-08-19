add_executable( test01_libsagui main.c )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

target_link_libraries( test01_libsagui PUBLIC Library LIB_SAGUI_STATIC )
