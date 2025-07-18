set_property(DIRECTORY PROPERTY LABELS C11_Annex_K)

set(CMAKE_C_STANDARD 11)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# speeds testing up to 2x

set(CMAKE_REQUIRED_DEFINITIONS -D__STDC_WANT_LIB_EXT1__=1)

check_symbol_exists(__STDC_LIB_EXT1__ "" c11_lib_ext1)
check_symbol_exists(ignore_handler_s "stdlib.h" c11_ignore_handler_s)
check_symbol_exists(constraint_handler_s "stdlib.h" c11_constraint_handler_s)
check_symbol_exists(snprintf_s "stdio.h" c11_snprintf_s)
check_symbol_exists(strcpy_s "string.h" c11_strcpy_s)
check_symbol_exists(strnlen_s "string.h" c11_strnlen_s)
check_symbol_exists(getenv_s "stdlib.h" c11_getenv_s)
check_symbol_exists(tmpnam_s "stdio.h" c11_tmpnam_s)
check_symbol_exists(tmpfile_s "stdio.h" c11_tmpfile_s)


foreach(t IN LISTS c11annex)
  if(c11_${t} AND EXISTS ${t}.c)
    add_executable(${t} ${t}.c)

    if(c11_strcpy_s AND c11_constraint_handler_s OR NOT MSVC AND t STREQUAL "strcpy_s")
      add_test(NAME strcpy_s COMMAND strcpy_s)
    elseif(t STREQUAL "strcpy_s")
    # MSVC error handler trips, but didn't yet support constraint_handler_s
      add_test(NAME strcpy_s
      COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:strcpy_s> -P ${PROJECT_SOURCE_DIR}/cmake/will_fail.cmake
      )
      set_property(TEST strcpy_s PROPERTY WILL_FAIL TRUE)
    else()
      add_test(NAME C11_${t} COMMAND ${t})
    endif()
  endif()
endforeach()
