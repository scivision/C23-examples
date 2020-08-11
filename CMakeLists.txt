cmake_minimum_required(VERSION 3.13)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug or Release")
endif()
project(DemoC11 LANGUAGES C)
enable_testing()

include(CheckCSourceCompiles)

add_subdirectory(c99)

add_subdirectory(c11)
