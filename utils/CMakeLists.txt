
set( UTILS_MODULE_ROOT_DIR ${CMAKE_SOURCE_DIR}/utils )

set(

  UTILS_MODULE_COMMON_SOURCES

)

# add_library(
#
#   UTILS_MODULE STATIC
#
#   ${UTILS_MODULE_COMMON_SOURCES}
#
# )
#
# target_link_libraries(
#
#   UTILS_MODULE PUBLIC
#
#   EXPORT_UTILS_MODULE_COMMON_HEADERS_DIRECTORIES
#
# )

if( UTILS_MODULE_TESTS )

  include( setup_tests.cmake )

endif()
