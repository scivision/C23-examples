cmake_minimum_required(VERSION 3.13)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug or Release")
endif()
project(DemoC11 LANGUAGES C)

if(NOT MSVC OR CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 19.27)
  add_subdirectory(c11)
endif()

add_subdirectory(c99)
