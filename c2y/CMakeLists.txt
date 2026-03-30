set_property(DIRECTORY PROPERTY LABELS C2Y)


if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_C_COMPILER_VERSION VERSION_LESS 15)
    return()
  endif()
  set(c2y_flags -std=c2y)
elseif(CMAKE_C_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_C_COMPILER_VERSION VERSION_LESS 19)
    return()
  endif()
  set(c2y_flags -std=c2y)
endif()

if(DEFINED c2y_flags)
  add_compile_options(${c2y_flags})
  set(CMAKE_REQUIRED_FLAGS ${c2y_flags})
endif()

file(READ if_declaration.c _src)
check_source_compiles(C "${_src}" c2y_if_declaration)

file(READ break_label.c _src)
check_source_compiles(C "${_src}" c2y_break_label)

foreach(t IN LISTS c2yfeatures)
  if(c2y_${t})
    add_executable(${t} ${t}.c)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()
