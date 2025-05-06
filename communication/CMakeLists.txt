
set( COMMUNICATION_MODULE_ROOT_DIR ${CMAKE_SOURCE_DIR}/communication )

set(

  COMMUNICATION_MODULE_COMMON_SOURCES

  ## IP ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/ip/ip_v4.cpp
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/ip/ip_v6.cpp

  ## SOCKET ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/socket/socket_context.cpp
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/socket/connection_socket_helper.cpp
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/socket/server_socket_helper.cpp
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/socket/socket_helper.cpp

  ## CONNECTION ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/connection/connection.cpp

  ## SERVER ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/server/server.cpp

  ## PACKET ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/packet/packet_headers.cpp
  ${COMMUNICATION_MODULE_ROOT_DIR}/src/packet/packet.cpp

)

set(

  COMMUNICATION_MODULE_COMMON_HEADERS_DIRECTORIES

  ## IP ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/include/ip

  ## SOCKET ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/include/socket

  ## CONNECTION ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/include/connection

  ## SERVER ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/include/server

  ## PACKET ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/include/packet

  ## PROTOCOLS ##
  ${COMMUNICATION_MODULE_ROOT_DIR}/include/protocols

  ../protocols/include/base_protocol

)

add_library(

  COMMUNICATION_MODULE STATIC

  ${COMMUNICATION_MODULE_COMMON_SOURCES}

)

target_include_directories(
  
  COMMUNICATION_MODULE PUBLIC

  ${COMMUNICATION_MODULE_COMMON_HEADERS_DIRECTORIES}

)