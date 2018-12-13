file(GLOB HEADERS "include/bravo/app/*.hpp")

add_library( bravo_app
             database_api.cpp
             api.cpp
             application.cpp
             impacted.cpp
             plugin.cpp
             ${HEADERS}
           )

target_link_libraries( bravo_app bravo_chain bravo_protocol bravo_tags bravo_follow bravo_witness bravo_mf_plugins fc graphene_net graphene_utilities )
target_include_directories( bravo_app
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( application.cpp api.cpp database_api.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

INSTALL( TARGETS
   bravo_app

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
INSTALL( FILES ${HEADERS} DESTINATION "include/bravo/app" )
