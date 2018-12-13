file(GLOB HEADERS "include/bravo/witness/*.hpp")

add_library( bravo_witness
             witness_plugin.cpp
             witness_evaluators.cpp
             witness_operations.cpp
           )

target_link_libraries( bravo_witness bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_witness
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

install( TARGETS
   bravo_witness

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
