file(GLOB HEADERS "include/bravo/tags/*.hpp")

add_library( bravo_tags
             tags_plugin.cpp )

target_link_libraries( bravo_tags bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_tags
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_tags

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
