
set( DIAGNOSTICS_MODULE_LOG_TESTS "diagnostics_module_log_tests" )
add_executable( ${DIAGNOSTICS_MODULE_LOG_TESTS} ${CMAKE_CURRENT_LIST_DIR}/src/log/log_tests.cpp )
target_link_libraries( ${DIAGNOSTICS_MODULE_LOG_TESTS} DIAGNOSTICS_MODULE EXPORT_DIAGNOSTICS_MODULE_COMMON_HEADERS_DIRECTORIES )
add_test( LOG_TESTS ${BUILD_BIN_DIR}/diagnostics_module_log_tests )

set( DIAGNOSTICS_MODULE_VALIDATION_TESTS "diagnostics_module_validation_tests" )
add_executable( ${DIAGNOSTICS_MODULE_VALIDATION_TESTS} ${CMAKE_CURRENT_LIST_DIR}/src/validation/validation_tests.cpp )
target_link_libraries( ${DIAGNOSTICS_MODULE_VALIDATION_TESTS} DIAGNOSTICS_MODULE EXPORT_DIAGNOSTICS_MODULE_COMMON_HEADERS_DIRECTORIES )
add_test( VALIDATION_TESTS ${BUILD_BIN_DIR}/diagnostics_module_log_tests )
