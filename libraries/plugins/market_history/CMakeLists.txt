file(GLOB HEADERS "include/bravo/market_history/*.hpp")

add_library( bravo_market_history
             market_history_plugin.cpp
             market_history_api.cpp
           )

target_link_libraries( bravo_market_history bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_market_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_market_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)