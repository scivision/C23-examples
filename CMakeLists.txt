cmake_minimum_required(VERSION 3.19...3.21)

project(DemoC11
  LANGUAGES C)

enable_testing()

include(CheckSourceCompiles)

add_subdirectory(c99)

add_subdirectory(c11)
