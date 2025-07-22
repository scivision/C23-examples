cmake_minimum_required(VERSION 3.25...4.2)
# CMake 3.21 required for C23 support.
# 3.25 for block()

project(C23examples LANGUAGES C)

enable_testing()

include(CheckIncludeFile)
include(CheckSourceCompiles)
include(CheckSymbolExists)

option(cppcheck "Run cppcheck")

check_include_file(stdlib.h HAVE_STDLIB)
if(NOT HAVE_STDLIB)
  message(FATAL_ERROR "stdlib.h not found")
endif()

if(MSVC)
  set(CMAKE_REQUIRED_FLAGS "/WX")
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  set(CMAKE_REQUIRED_FLAGS "-Werror")
  add_compile_options(-Wall -Wextra -Wno-unused-variable)
  # makes unsupported attributes checks error.
endif()

# CPPcheck
if(cppcheck)
  find_program(cppcheck_exe NAMES cppcheck REQUIRED)
  set(cppcheck_opts --enable=all --inline-suppr --quiet --suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck.supp)
  set(CMAKE_C_CPPCHECK ${cppcheck_exe} --std=c23 ${cppcheck_opts})
endif()

# --- examples
set(c99features designated restrict)

set(c11features generic c11noreturn vla)

set(c11annexfeatures getenv_s tmpnam_s tmpfile_s strcpy_s)

set(c23features bool has_include
fallthrough maybe_unused
nodiscard noreturn nullptr
strdup strndup
constexpr limits reproducible unsequenced
static_assert
unreachable
)

set(stds c99 c11 c11annex c23)

foreach(s IN LISTS stds)
  add_subdirectory(${s})
endforeach()

file(GENERATE OUTPUT .gitignore CONTENT "*")

# --- count features enabled by language standard
include(cmake/features.cmake)
