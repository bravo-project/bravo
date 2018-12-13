file(GLOB HEADERS "include/bravo/plugins/auth_util/*.hpp")

add_library( bravo_auth_util
             ${HEADERS}
             auth_util_plugin.cpp
             auth_util_api.cpp
           )

target_link_libraries( bravo_auth_util bravo_app bravo_chain bravo_protocol fc )
target_include_directories( bravo_auth_util
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
