# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# cs225_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225/project/lib/cs225/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225/project/lib/cs225/graph.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225/project/build/CMakeFiles/cmake.verify_globs")
endif()

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225/project/src/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225/project/src/graph_constructor.cpp"
  "/workspaces/cs225/project/src/info_constructor.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225/project/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:129 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/cs225/project/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/cs225/project/tests/testcases_BFS.cpp"
  "/workspaces/cs225/project/tests/testcases_Dij.cpp"
  "/workspaces/cs225/project/tests/testcases_data.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/cs225/project/build/CMakeFiles/cmake.verify_globs")
endif()
