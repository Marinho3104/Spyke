cmake_minimum_required(VERSION 3.13)

project( Spyke )
set(CMAKE_CXX_STANDARD 17)

# Define files in other directories
file( GLOB_RECURSE GPU_MANAGEMENT_FILES CONFIGURE_DEPENDS "./gpu_management/*.cpp" )


# Executable used for the compilation
if( GPU_MANAGEMENT )

  add_executable( Spyke "./tests/gpu_management/main.cpp" ${GPU_MANAGEMENT_FILES} )

else()

endif()

# External libraries

find_package(OpenCL REQUIRED)
target_link_libraries(Spyke OpenCL::OpenCL)

