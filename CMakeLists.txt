cmake_minimum_required(VERSION 3.19...3.25)

project(DemoC23
LANGUAGES C)

enable_testing()

include(CheckSourceCompiles)

# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

set(CMAKE_C_STANDARD 23)

# examples

add_subdirectory(c99)

add_subdirectory(c11)

add_subdirectory(c23)
