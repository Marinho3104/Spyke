cmake_minimum_required(VERSION 3.5)

project( Spyke )
set(CMAKE_CXX_STANDARD 17)


SET( CMAKE_CXX_FLAGS_DEBUG  "")
SET( CMAKE_CXX_FLAGS_RELEASE  "")

if( SANITIZE )

  SET( CMAKE_CXX_FLAGS  "-g -fsanitize=address")

else()

  SET( CMAKE_CXX_FLAGS  "")

endif()


file(GLOB SPYKE_TYPES "./types/*")
file(GLOB SPYKE_TESTS_TYPES "./tests/types/*.cpp")
add_executable( ${PROJECT_NAME} ${SPYKE_TESTS_TYPES} ${SPYKE_TYPES} )


add_subdirectory( ./libs/cipher )
target_link_directories( ${PROJECT_NAME} PRIVATE cipher )

file(GLOB ED25519_LIB "./libs/ed25519/src/*.c")
add_library( ed25519 ${ED25519_LIB} )
target_link_directories( ${PROJECT_NAME} PRIVATE ed25519 )

target_link_libraries( ${PROJECT_NAME} cipher ed25519 )



