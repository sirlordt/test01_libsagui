add_executable( test02 main.c )

set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

target_link_libraries( test02 PUBLIC Library LIB_SAGUI_STATIC )
