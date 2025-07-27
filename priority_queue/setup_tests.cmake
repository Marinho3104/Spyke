
set( PRIORITY_QUEUE_MODULE_TESTS "priority_queue_module_tests" )
add_executable( ${PRIORITY_QUEUE_MODULE_TESTS} ${CMAKE_CURRENT_LIST_DIR}/src/priority_queue_tests.cpp )
target_link_libraries( ${PRIORITY_QUEUE_MODULE_TESTS} PRIORITY_QUEUE_MODULE DIAGNOSTICS_MODULE )
add_test( PRIORITY_QUEUE_TESTS ${BUILD_BIN_DIR}/priority_queue_module_tests )
