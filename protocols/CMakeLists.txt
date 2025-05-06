
set( PROTOCOLS_MODULE_ROOT_DIR ${CMAKE_SOURCE_DIR}/protocols )

set(

  PROTOCOLS_MODULE_COMMON_SOURCES

  ## DISCONNECT PROTOCOL ##
  ${PROTOCOLS_MODULE_ROOT_DIR}/src/disconnect_protocol/disconnect_protocol.cpp

  ## BASE PROTOCOL ##
  ${PROTOCOLS_MODULE_ROOT_DIR}/src/base_protocol/base_protocol.cpp
  
)

set(

  PROTOCOLS_MODULE_COMMON_HEADERS_DIRECTORIES

  ## BASE PROTOCOL ##
  ${PROTOCOLS_MODULE_ROOT_DIR}/include/base_protocol

  ## DISCONNECT PROTOCOL ##
  ${PROTOCOLS_MODULE_ROOT_DIR}/include/disconnect_protocol

  ../communication/include/packet

)

add_library(

  PROTOCOLS_MODULE STATIC

  ${PROTOCOLS_MODULE_COMMON_SOURCES}

)

target_include_directories(
  
  PROTOCOLS_MODULE PUBLIC

  ${PROTOCOLS_MODULE_COMMON_HEADERS_DIRECTORIES}

)