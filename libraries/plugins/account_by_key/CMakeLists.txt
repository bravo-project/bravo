file(GLOB HEADERS "include/bravo/account_by_key/*.hpp")

add_library( bravo_account_by_key
             account_by_key_plugin.cpp
             account_by_key_api.cpp
           )

target_link_libraries( bravo_account_by_key bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_account_by_key
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_account_by_key

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
