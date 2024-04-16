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

file( GLOB_RECURSE NODE_FILES CONFIGURE_DEPENDS "./node/*.cpp" )
file( GLOB_RECURSE P2P_FILES CONFIGURE_DEPENDS "./p2p/*.cpp" )



if(NODE1)

  add_executable( Spyke "./tests/node/main.cpp" ${NODE_FILES} ${P2P_FILES} )

elseif(NODE2)

  add_executable( Spyke "./tests/node/main1.cpp" ${NODE_FILES} ${P2P_FILES} )

endif()

