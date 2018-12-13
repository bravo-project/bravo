file(GLOB HEADERS "include/bravo/plugins/block_info/*.hpp")

add_library( bravo_block_info
             ${HEADERS}
             block_info_plugin.cpp
             block_info_api.cpp
           )

target_link_libraries( bravo_block_info bravo_app bravo_chain bravo_protocol fc )
target_include_directories( bravo_block_info
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
