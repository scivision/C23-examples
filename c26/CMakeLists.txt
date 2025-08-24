set_property(DIRECTORY PROPERTY LABELS C26)

set(CMAKE_C_STANDARD 26)


if(CMAKE_VERSION VERSION_LESS 4.2)
  if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_C_COMPILER_VERSION VERSION_LESS 15)
      return()
    endif()
    set(c26_flags -std=c2y)
  elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    if(CMAKE_C_COMPILER_VERSION VERSION_LESS 19)
      return()
    endif()
    set(c26_flags -std=c2y)
  endif()
endif()

if(DEFINED c26_flags)
  add_compile_options(${c26_flags})
  set(CMAKE_REQUIRED_FLAGS ${c26_flags})
endif()

file(READ if_declaration.c _src)
check_source_compiles(C "${_src}" c26_if_declaration)

file(READ break_label.c _src)
check_source_compiles(C "${_src}" c26_break_label)

foreach(t IN LISTS c26features)
  if(c26_${t})
    add_executable(${t} ${t}.c)
    if(NOT t STREQUAL unreachable)
      add_test(NAME ${t} COMMAND ${t})
    endif()
  endif()
endforeach()
