cmake_minimum_required(VERSION 3.24)

project( Spyke )
set(CMAKE_CXX_STANDARD 17)

if(EXAMPLE)
  add_executable( Spyke "./tests/example1/main.cpp" )
else()
  add_executable( Spyke "./tests/example2/main.cpp" )
endif()

