
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Spyke 
  VERSION 1.0
  LANGUAGES CXX
)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(CMAKE_CXX_FLAGS "-std=c++17")

set( BUILD_DIR ${CMAKE_SOURCE_DIR}/build )
set( BUILD_BIN_DIR ${BUILD_DIR}/bin )
set( BUILD_OBJ_DIR ${BUILD_DIR}/obj )
set( BUILD_LIB_DIR ${BUILD_DIR}/lib )

set( MAIN_FILE_PATH ${CMAKE_SOURCE_DIR}/src/main.cpp )

set( SUB_DIRECTORIES_COMMUNICATION_PATH ${CMAKE_SOURCE_DIR}/communication/ )
set( SUB_DIRECTORIES_PROTOCOLS_PATH ${CMAKE_SOURCE_DIR}/protocols/ )


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_BIN_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_LIB_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${build_LIB_dir} )

enable_testing()

add_subdirectory(
  ${SUB_DIRECTORIES_COMMUNICATION_PATH}
)

add_subdirectory(
  ${SUB_DIRECTORIES_PROTOCOLS_PATH}
)


add_executable(
  ${CMAKE_PROJECT_NAME}
  ${MAIN_FILE_PATH}
)


target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  COMMUNICATION_MODULE
  PROTOCOLS_MODULE
)


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

set( PROTOCOLS_MODULE_PROTOCOLS_TESTS "protocols_module_protocols_tests" )
add_executable( ${PROTOCOLS_MODULE_PROTOCOLS_TESTS} protocols/src/protocols_tests.cpp )
target_link_libraries( ${PROTOCOLS_MODULE_PROTOCOLS_TESTS} PROTOCOLS_MODULE )
add_test( PROTOCOLS_TEST ${BUILD_BIN_DIR}/protocols_module_protocols_tests )
