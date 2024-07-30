cmake_minimum_required(VERSION 3.24)

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
file( GLOB_RECURSE ASSEMBLER CONFIGURE_DEPENDS "./assembler/*.cpp" )

if(ASSEMBLER)
  add_executable( Spyke "./tests/assembler/main.cpp" ${ASSEMBLER} )
endif()

