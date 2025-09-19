
get_filename_component(MODULE_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
file(GLOB_RECURSE DEMO_SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/demos/*")

foreach(DEMO_SOURCE_FILE ${DEMO_SOURCE_FILES})

  get_filename_component(DEMO_FILE_NAME ${DEMO_SOURCE_FILE} NAME_WE)
  
  set( DEMO_NAME "${MODULE_NAME}_module_${DEMO_FILE_NAME}" )
  add_executable(${DEMO_NAME} ${DEMO_SOURCE_FILE})
  target_link_libraries(${DEMO_NAME} ${MODULE_NAME}_MODULE)

endforeach()
