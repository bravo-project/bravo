file(GLOB HEADERS "include/bravo/account_history/*.hpp")

add_library( bravo_account_history
             account_history_plugin.cpp
           )

target_link_libraries( bravo_account_history bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_account_history
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_account_history

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
