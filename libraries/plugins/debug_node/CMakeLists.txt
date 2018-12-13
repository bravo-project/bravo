file(GLOB HEADERS "include/bravo/plugins/debug_node/*.hpp")

add_library( bravo_debug_node
             ${HEADERS}
             debug_node_plugin.cpp
             debug_node_api.cpp
           )

target_link_libraries( bravo_debug_node bravo_app bravo_chain bravo_protocol fc )
target_include_directories( bravo_debug_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS bravo_debug_node
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
       )
INSTALL( FILES ${HEADERS} DESTINATION "include/bravo/plugins/debug_node" )
