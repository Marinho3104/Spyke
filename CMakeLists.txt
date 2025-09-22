
cmake_minimum_required(VERSION 3.15...3.31)

project(
  Spyke 
  VERSION 1.0
  LANGUAGES CXX
)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set( CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra -Werror" )
set( CMAKE_BUILD_TYPE Debug )


set( BUILD_DIR ${CMAKE_SOURCE_DIR}/build )
set( BUILD_BIN_DIR ${BUILD_DIR}/bin )
set( BUILD_OBJ_DIR ${BUILD_DIR}/obj )
set( BUILD_LIB_DIR ${BUILD_DIR}/lib )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_BIN_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_LIB_DIR} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_LIB_DIR} )

# This flag is used to invert the includes use on templates
# implementation and defintion
add_compile_definitions( -DENABLE_TEMPLATE_COMPILATION )

set(

  MODULE_NAMES

  diagnostics
  priority_queue
  utils

)


enable_testing()

foreach(module_name IN LISTS MODULE_NAMES)

  include( ${CMAKE_SOURCE_DIR}/${module_name}/export_headers.cmake )

endforeach()

foreach(module_name IN LISTS MODULE_NAMES)

  add_subdirectory( ${CMAKE_SOURCE_DIR}/${module_name} )

endforeach()

foreach(module_name IN LISTS MODULE_NAMES)

  string(TOUPPER "${module_name}" MODULE_NAME_UPPERCASE)

  include( ${CMAKE_SOURCE_DIR}/${module_name}/demos.cmake )

  if( ${MODULE_NAME_UPPERCASE}_TESTS_ENABLE )
    include( ${CMAKE_SOURCE_DIR}/${module_name}/tests.cmake )
  endif()

endforeach()
