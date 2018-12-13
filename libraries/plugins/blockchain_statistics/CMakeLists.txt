file(GLOB HEADERS "include/bravo/blockchain_statistics/*.hpp")

add_library( bravo_blockchain_statistics
             blockchain_statistics_plugin.cpp
             blockchain_statistics_api.cpp
           )

target_link_libraries( bravo_blockchain_statistics bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_blockchain_statistics
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_blockchain_statistics

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)