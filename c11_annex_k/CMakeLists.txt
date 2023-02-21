set_property(DIRECTORY PROPERTY LABELS C11_Annex_K)

message("C11 Annex K functions are not generally available, except for MSVC-like compilers.")

set(CMAKE_REQUIRED_DEFINITIONS -D__STDC_WANT_LIB_EXT1__=1)

check_symbol_exists(__STDC_LIB_EXT1__ "" c11_lib_ext1)
check_symbol_exists(ignore_handler_s "stdlib.h" c11_ignore_handler_s)
check_symbol_exists(constraint_handler_s "stdlib.h" c11_constraint_handler_s)
check_symbol_exists(snprintf_s "stdio.h" c11_snprintf_s)
check_symbol_exists(strcpy_s "string.h" c11_strcpy_s)
check_symbol_exists(strlen_s "string.h" c11_strlen_s)
check_symbol_exists(getenv_s "stdlib.h" c11_getenv_s)
check_symbol_exists(tmpnam_s "stdio.h" c11_tmpnam_s)
check_symbol_exists(tmpfile_s "stdio.h" c11_tmpfile_s)

# --- strcpy_s
if(c11_strcpy_s)
  add_executable(strcpy_s strcpy_s.c)
  if(c11_constraint_handler_s OR NOT MSVC)
    add_test(NAME strcpy_s COMMAND strcpy_s)
  else()
  # MSVC error handler trips, but didn't yet support constraint_handler_s
    add_test(NAME strcpy_s
    COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:strcpy_s> -P ${PROJECT_SOURCE_DIR}/cmake/will_fail.cmake
    )
    set_property(TEST strcpy_s PROPERTY WILL_FAIL TRUE)
  endif()
endif()

foreach(t IN ITEMS getenv_s tmpnam_s tmpfile_s)
  if(c11_${t})
    add_executable(C11_${t} ${t}.c)
    add_test(NAME C11_${t} COMMAND C11_${t})
  endif()
endforeach()
