cmake_minimum_required(VERSION 3.13)

project( Spyke )
set(CMAKE_CXX_STANDARD 17)

include( CheckCXXCompilerFlag )

check_cxx_compiler_flag(-fsanitize=address ASAN_AVAILABLE )


SET( CMAKE_CXX_FLAGS_DEBUG  "")
SET( CMAKE_CXX_FLAGS_RELEASE  "")

if( SANITIZE )

  SET( CMAKE_CXX_FLAGS  "-g -fsanitize=address")

else()

  SET( CMAKE_CXX_FLAGS  "")

endif()

# Define files in other directories
file( GLOB_RECURSE GPU_MANAGEMENT_FILES CONFIGURE_DEPENDS "./gpu_management/*.cpp" )
file( GLOB_RECURSE TRANSACTIONS_MANAGEMENT_GPU_FILES CONFIGURE_DEPENDS "./transaction_management_gpu/*.cpp" )
file( GLOB_RECURSE UTILS_FILES CONFIGURE_DEPENDS "./utils/*.cpp" )


# Executable used for the compilation
if( GPU_MANAGEMENT )

  add_executable( Spyke "./tests/gpu_management/main.cpp" ${GPU_MANAGEMENT_FILES} ${TRANSACTIONS_MANAGEMENT_GPU_FILES} ${UTILS_FILES} )

else( TRANSACTIONS_MANAGEMENT_GPU )

  add_executable( Spyke "./tests/transaction_management_gpu/main.cpp" ${GPU_MANAGEMENT_FILES} ${TRANSACTIONS_MANAGEMENT_GPU_FILES} ${UTILS_FILES} )

endif()


# External libraries
find_package(OpenCL REQUIRED)
target_link_libraries(Spyke OpenCL::OpenCL)

