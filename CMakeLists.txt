cmake_minimum_required(VERSION 3.19...3.26)

project(C23examples LANGUAGES C)

enable_testing()

include(CheckIncludeFile)
include(CheckSourceCompiles)
include(CheckSymbolExists)

set(CMAKE_C_STANDARD 23)

if(MSVC)
  list(APPEND CMAKE_REQUIRED_FLAGS /WX)
elseif(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|^Intel")
  list(APPEND CMAKE_REQUIRED_FLAGS -Werror)
  # makes unsupported attributes checks error.
endif()

# --- examples

foreach(s IN ITEMS c99 c11 c11_annex_k c23 posix)
  add_subdirectory(${s})
endforeach()

file(GENERATE OUTPUT .gitignore CONTENT "*")
