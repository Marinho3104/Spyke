# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.29
cmake_policy(SET CMP0009 NEW)

# NODE_FILES at CMakeLists.txt:25 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/marinho/Projects/Own/Spyke/./node/*.cpp")
set(OLD_GLOB
  "/home/marinho/Projects/Own/Spyke/./node/node.cpp"
  "/home/marinho/Projects/Own/Spyke/./node/node_configuration.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/marinho/Projects/Own/Spyke/build1/CMakeFiles/cmake.verify_globs")
endif()

# P2P_FILES at CMakeLists.txt:26 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/marinho/Projects/Own/Spyke/./p2p/*.cpp")
set(OLD_GLOB
  "/home/marinho/Projects/Own/Spyke/./p2p/IP_connection.cpp"
  "/home/marinho/Projects/Own/Spyke/./p2p/connection.cpp"
  "/home/marinho/Projects/Own/Spyke/./p2p/open_connection.cpp"
  "/home/marinho/Projects/Own/Spyke/./p2p/open_server_connection.cpp"
  "/home/marinho/Projects/Own/Spyke/./p2p/socket.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/marinho/Projects/Own/Spyke/build1/CMakeFiles/cmake.verify_globs")
endif()