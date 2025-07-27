
set( UTILS_MODULE_SMART_POINTERS_TESTS "utils_module_smart_pointers_tests" )
add_executable( ${UTILS_MODULE_SMART_POINTERS_TESTS} ${CMAKE_CURRENT_LIST_DIR}/src/smart_pointers/smart_pointers_tests.cpp )
target_link_libraries( ${UTILS_MODULE_SMART_POINTERS_TESTS} EXPORT_UTILS_MODULE_COMMON_HEADERS_DIRECTORIES )
add_test( SMART_POINTERS_TESTS ${BUILD_BIN_DIR}/utils_module_smart_pointers_tests )
