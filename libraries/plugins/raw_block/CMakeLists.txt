file(GLOB HEADERS "include/bravo/plugins/raw_block/*.hpp")

add_library( bravo_raw_block
             ${HEADERS}
             raw_block_plugin.cpp
             raw_block_api.cpp
           )

target_link_libraries( bravo_raw_block bravo_app bravo_chain bravo_protocol fc )
target_include_directories( bravo_raw_block
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
