
set(

  COMMON_SOURCES

  ## IP ##
  src/ip/ip_v4.cpp
  src/ip/ip_v6.cpp

  ## SOCKET ##
  src/socket/socket_context.cpp
  src/socket/connection_socket_helper.cpp
  src/socket/server_socket_helper.cpp
  src/socket/socket_helper.cpp

  ## CONNECTION ##
  src/connection/connection.cpp

  ## SERVER ##
  src/server/server.cpp

  ## PACKET ##
  src/packet/packet_headers.cpp
  src/packet/packet.cpp

)

set(

  COMMON_HEADERS_DIRECTORIES

  ## IP ##
  include/ip

  ## SOCKET ##
  include/socket

  ## CONNECTION ##
  include/connection

  ## SERVER ##
  include/server

  ## PACKET ##
  include/packet

  ## PROTOCOLS ##
  include/protocols

)

add_library(

  COMMUNICATION_MODULE STATIC

  ${COMMON_SOURCES}

)

target_include_directories(
  
  COMMUNICATION_MODULE PUBLIC

  ${COMMON_HEADERS_DIRECTORIES}

)

set( COMMUNICATION_MODULE_IP_V4_TESTS "communication_module_ip_v4_tests" )
add_executable( ${COMMUNICATION_MODULE_IP_V4_TESTS} src/ip/ip_v4_tests.cpp )
target_link_libraries( ${COMMUNICATION_MODULE_IP_V4_TESTS} COMMUNICATION_MODULE )
add_test( IP_V4_TEST ${BUILD_BIN_DIR}/communication_module_ip_v4_tests )

set( COMMUNICATION_MODULE_IP_V6_TESTS "communication_module_ip_v6_tests" )
add_executable( ${COMMUNICATION_MODULE_IP_V6_TESTS} src/ip/ip_v6_tests.cpp )
target_link_libraries( ${COMMUNICATION_MODULE_IP_V6_TESTS} COMMUNICATION_MODULE )
add_test( IP_V6_TEST ${BUILD_BIN_DIR}/communication_module_ip_v6_tests )

set( COMMUNICATION_MODULE_CONNECTION_TESTS "communication_module_connection_tests" )
add_executable( ${COMMUNICATION_MODULE_CONNECTION_TESTS} src/connection/connection_tests.cpp )
target_link_libraries( ${COMMUNICATION_MODULE_CONNECTION_TESTS} COMMUNICATION_MODULE )
add_test( CONNECTION_TEST ${BUILD_BIN_DIR}/communication_module_connection_tests )

set( COMMUNICATION_MODULE_SERVER_TESTS "communication_module_server_tests" )
add_executable( ${COMMUNICATION_MODULE_SERVER_TESTS} src/server/server_tests.cpp )
target_link_libraries( ${COMMUNICATION_MODULE_SERVER_TESTS} COMMUNICATION_MODULE )
add_test( SERVER_TEST ${BUILD_BIN_DIR}/communication_module_server_tests )

set( COMMUNICATION_MODULE_PACKET_TESTS "communication_module_packet_tests" )
add_executable( ${COMMUNICATION_MODULE_PACKET_TESTS} src/packet/packet_tests.cpp )
target_link_libraries( ${COMMUNICATION_MODULE_PACKET_TESTS} COMMUNICATION_MODULE )
add_test( PACKET_TEST ${BUILD_BIN_DIR}/communication_module_packet_tests )