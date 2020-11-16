cmake_minimum_required(VERSION 3.13)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug or Release")
endif()

project(DemoC11
LANGUAGES C)

include(CTest)
include(CheckCSourceCompiles)

# this helps linters e.g. Visual Studio Intellicode work properly
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

add_subdirectory(c99)

add_subdirectory(c11)
