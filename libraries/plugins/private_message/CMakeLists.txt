file(GLOB HEADERS "include/bravo/private_message/*.hpp")

add_library( bravo_private_message
             private_message_plugin.cpp
           )

target_link_libraries( bravo_private_message bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_private_message
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_private_message

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
