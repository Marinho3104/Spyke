
set( NODE_MODULE_ROOT_DIR ${CMAKE_SOURCE_DIR}/node )

set(

  NODE_MODULE_COMMON_SOURCES

  ## NODE ##
  ${NODE_MODULE_ROOT_DIR}/src/node.cpp

)

add_library(

  NODE_MODULE STATIC

  ${NODE_MODULE_COMMON_SOURCES}

)

target_link_libraries(

  NODE_MODULE PUBLIC

  EXPORT_NODE_MODULE_COMMON_HEADERS_DIRECTORIES

)

if( NODE_MODULE_TESTS )

  include( ${NODE_MODULE_ROOT_DIR}/setup_tests.cmake )

endif()
