cmake_minimum_required(VERSION 3.21...3.30)
# CMake 3.21 required for C23 support.

project(C23examples LANGUAGES C)

enable_testing()

include(CheckIncludeFile)
include(CheckSourceCompiles)
include(CheckSymbolExists)

set(CMAKE_C_STANDARD 23)

option(cppcheck "Run cppcheck")

if(MSVC)
  set(CMAKE_REQUIRED_FLAGS "/WX")
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  set(CMAKE_REQUIRED_FLAGS "-Werror")
  add_compile_options(-Wall -Wextra)
  # makes unsupported attributes checks error.
endif()

# CPPcheck
if(cppcheck)
  find_program(cppcheck_exe NAMES cppcheck REQUIRED)
  set(cppcheck_opts --enable=all --inline-suppr --quiet --suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck.supp)
  set(CMAKE_C_CPPCHECK ${cppcheck_exe} --std=c${CMAKE_C_STANDARD} ${cppcheck_opts})
endif()

# --- examples

foreach(s IN ITEMS c99 c11 c11_annex_k c23 posix)
  add_subdirectory(${s})
endforeach()

file(GENERATE OUTPUT .gitignore CONTENT "*")
