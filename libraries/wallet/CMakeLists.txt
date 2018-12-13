file(GLOB HEADERS "include/bravo/wallet/*.hpp")

find_package( Perl )
find_package( Doxygen )

if( PERL_FOUND AND DOXYGEN_FOUND AND NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja" )
  configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile )
  add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen/perlmod/DoxyDocs.pm
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      COMMAND ${DOXYGEN_EXECUTABLE}
                      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/include/bravo/wallet/wallet.hpp )

  add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp
                      COMMAND ${PERL_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/generate_api_documentation.pl ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp.new

                      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp.new ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp
                      COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp.new
                      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/generate_api_documentation.pl ${CMAKE_CURRENT_BINARY_DIR}/doxygen/perlmod/DoxyDocs.pm )
else()
  # no perl and doxygen, generate the best docs we can at runtime from reflection
  add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp
                      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/api_documentation_standin.cpp ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp
                      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/api_documentation_standin.cpp )
endif()

add_library( bravo_wallet wallet.cpp ${CMAKE_CURRENT_BINARY_DIR}/api_documentation.cpp ${HEADERS} )
# I don't know why bravo_app is required twice in the following line, I just know the linker breaks if it isn't.
target_link_libraries( bravo_wallet PRIVATE bravo_app graphene_net bravo_chain bravo_protocol graphene_utilities fc bravo_private_message bravo_app bravo_follow bravo_account_by_key ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} )
target_include_directories( bravo_wallet PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

if(MSVC)
  set_source_files_properties( wallet.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

install( TARGETS
   bravo_wallet

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${HEADERS} DESTINATION "include/bravo/wallet" )
