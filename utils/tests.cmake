
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
file(GLOB_RECURSE TEST_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/tests/*")

foreach(TEST_SOURCE_FILE ${TEST_SOURCE_FILES})

  get_filename_component(TEST_FILE_NAME ${TEST_SOURCE_FILE} NAME_WE)
  
  set( TEST_NAME "${MODULE_NAME}_module_${TEST_FILE_NAME}" )
  add_executable(${TEST_NAME} ${TEST_SOURCE_FILE})
  target_link_libraries(${TEST_NAME} ${MODULE_NAME}_MODULE)
  add_test(${TEST_NAME} ${BUILD_BIN_DIR}/${TEST_NAME})

endforeach()
