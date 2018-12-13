add_executable( bravod main.cpp )
if( UNIX AND NOT APPLE )
  set(rt_library rt )
endif()

find_package( Gperftools QUIET )
if( GPERFTOOLS_FOUND )
    message( STATUS "Found gperftools; compiling bravod with TCMalloc")
    list( APPEND PLATFORM_SPECIFIC_LIBS tcmalloc )
endif()

target_link_libraries( bravod PRIVATE
   bravo_plugins
   bravo_mf_plugins
   bravo_app
   bravo_witness
   bravo_account_history
   bravo_chain
   bravo_protocol
   fc
   ${CMAKE_DL_LIBS}
   ${PLATFORM_SPECIFIC_LIBS}
)

install( TARGETS 
   bravod

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
