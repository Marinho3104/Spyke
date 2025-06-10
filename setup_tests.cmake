
enable_testing()


if( COMMUNICATION_MODULE_TESTS )

  set( COMMUNICATION_MODULE_IP_V4_TESTS "communication_module_ip_v4_tests" )
  add_executable( ${COMMUNICATION_MODULE_IP_V4_TESTS} communication/src/ip/ip_v4_tests.cpp )
  target_link_libraries( ${COMMUNICATION_MODULE_IP_V4_TESTS} COMMUNICATION_MODULE )
  add_test( IP_V4_TEST ${BUILD_BIN_DIR}/communication_module_ip_v4_tests )

  set( COMMUNICATION_MODULE_IP_V6_TESTS "communication_module_ip_v6_tests" )
  add_executable( ${COMMUNICATION_MODULE_IP_V6_TESTS} communication/src/ip/ip_v6_tests.cpp )
  target_link_libraries( ${COMMUNICATION_MODULE_IP_V6_TESTS} COMMUNICATION_MODULE )
  add_test( IP_V6_TEST ${BUILD_BIN_DIR}/communication_module_ip_v6_tests )

  set( COMMUNICATION_MODULE_CONNECTION_TESTS "communication_module_connection_tests" )
  add_executable( ${COMMUNICATION_MODULE_CONNECTION_TESTS} communication/src/connection/connection_tests.cpp )
  target_link_libraries( ${COMMUNICATION_MODULE_CONNECTION_TESTS} COMMUNICATION_MODULE )
  add_test( CONNECTION_TEST ${BUILD_BIN_DIR}/communication_module_connection_tests )

  set( COMMUNICATION_MODULE_SERVER_TESTS "communication_module_server_tests" )
  add_executable( ${COMMUNICATION_MODULE_SERVER_TESTS} communication/src/server/server_tests.cpp )
  target_link_libraries( ${COMMUNICATION_MODULE_SERVER_TESTS} COMMUNICATION_MODULE )
  add_test( SERVER_TEST ${BUILD_BIN_DIR}/communication_module_server_tests )

  set( COMMUNICATION_MODULE_PACKET_TESTS "communication_module_packet_tests" )
  add_executable( ${COMMUNICATION_MODULE_PACKET_TESTS} communication/src/packet/packet_tests.cpp )
  target_link_libraries( ${COMMUNICATION_MODULE_PACKET_TESTS} COMMUNICATION_MODULE )
  add_test( PACKET_TEST ${BUILD_BIN_DIR}/communication_module_packet_tests )

endif()


if( PROTOCOLS_MODULE_TESTS )

  set( PROTOCOLS_MODULE_DISCONNECT_PROTOCOL_TESTS "protocols_module_disconnect_protocol_tests" )
  add_executable( ${PROTOCOLS_MODULE_DISCONNECT_PROTOCOL_TESTS} protocols/src/disconnect_protocol/disconnect_protocol_tests.cpp )
  target_link_libraries( ${PROTOCOLS_MODULE_DISCONNECT_PROTOCOL_TESTS} COMMUNICATION_MODULE PROTOCOLS_MODULE )
  add_test( DISCONNECT_PROTOCOL_TEST ${BUILD_BIN_DIR}/protocols_module_disconnect_protocol_tests )

endif()


if( PRIORITY_QUEUE_MODULE_TESTS )

endif()


if( UTILS_MODULE_TESTS )

  set( UTILS_MODULE_SMART_POINTERS_TESTS "utils_module_smart_pointers_tests" )
  add_executable( ${UTILS_MODULE_SMART_POINTERS_TESTS} utils/src/smart_pointers/smart_pointers_tests.cpp )
  target_link_libraries( ${UTILS_MODULE_SMART_POINTERS_TESTS} EXPORT_UTILS_MODULE_COMMON_HEADERS_DIRECTORIES )
  add_test( SMART_POINTERS_TESTS ${BUILD_BIN_DIR}/utils_module_smart_pointers_tests )

endif()
