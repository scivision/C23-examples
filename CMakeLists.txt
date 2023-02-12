cmake_minimum_required(VERSION 3.19...3.26)

project(DemoC23 LANGUAGES C)

enable_testing()

include(CheckIncludeFile)
include(CheckSourceCompiles)
include(CheckSymbolExists)

set(CMAKE_C_STANDARD 23)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  list(APPEND CMAKE_REQUIRED_FLAGS -Werror)
  # makes unsupported attributes checks error.
endif()

# --- examples

foreach(s IN ITEMS c99 c11 c23 posix)
  add_subdirectory(${s})
endforeach()
# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()
