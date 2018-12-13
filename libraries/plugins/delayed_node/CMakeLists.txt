file(GLOB HEADERS "include/bravo/delayed_node/*.hpp")

add_library( bravo_delayed_node
             delayed_node_plugin.cpp
           )

target_link_libraries( bravo_delayed_node bravo_chain bravo_protocol bravo_app )
target_include_directories( bravo_delayed_node
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( delayed_node_plugin.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   bravo_delayed_node

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
