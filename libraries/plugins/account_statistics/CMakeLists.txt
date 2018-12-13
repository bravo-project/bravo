file(GLOB HEADERS "include/bravo/account_statistics/*.hpp")

add_library( bravo_account_statistics
             account_statistics_plugin.cpp
             account_statistics_api.cpp
           )

target_link_libraries( bravo_account_statistics bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_account_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_account_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)