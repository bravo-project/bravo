file(GLOB HEADERS "include/bravo/follow/*.hpp")

add_library( bravo_follow
             follow_plugin.cpp
             follow_api.cpp
             follow_operations.cpp
             follow_evaluators.cpp
           )

target_link_libraries( bravo_follow bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_follow
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_follow

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
