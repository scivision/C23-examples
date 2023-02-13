set_property(DIRECTORY PROPERTY LABELS C11)

message(STATUS "C11 configuration checks:")

set(CMAKE_REQUIRED_DEFINITIONS -D__STDC_WANT_LIB_EXT1__=1)

check_symbol_exists(__STDC_LIB_EXT1__ "stdlib.h" c11_lib_ext1)
check_symbol_exists(ignore_handler_s "stdlib.h" c11_ignore_handler_s)
check_symbol_exists(constraint_handler_s "stdlib.h" c11_constraint_handler_s)
check_symbol_exists(snprintf_s "stdio.h" c11_snprintf_s)
check_symbol_exists(strcpy_s "string.h" c11_strcpy_s)
check_symbol_exists(strlen_s "string.h" c11_strlen_s)
check_symbol_exists(static_assert "assert.h" c11_static_assert)
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

# --- Generic
file(READ generic.c _src)
check_source_compiles(C "${_src}" c11_generic)


# --- C11 noreturn
check_source_compiles(C
"#include <stdlib.h>
#include <stdnoreturn.h>
noreturn void f(){ exit(0); }
int main(void) { f(); return EXIT_FAILURE; }"
c11_noreturn
)

foreach(t IN ITEMS generic getenv_s noreturn static_assert tmpnam_s tmpfile_s)
  if(c11_${t})
    add_executable(C11_${t} ${t}.c)
    add_test(NAME C11_${t} COMMAND C11_${t})
  endif()
endforeach()


# --- variable length array
check_source_compiles(C
"int main(void){for (int i = 1; i < 5; i++){int a[i];} return 0;}"
c11_vla
)
if(c11_vla)
  add_executable(vla vla.c)
  add_test(NAME VariableLengthArray COMMAND vla 3)
  set_property(TEST VariableLengthArray PROPERTY PASS_REGULAR_EXPRESSION "^1 2 3[ \t\r\n]+$")
endif()

# --- threading
check_include_file(threads.h c11_thread_h)
if(c11_thread_h)
  check_source_compiles(C
  "#include <threads.h>
  int main(void){ thrd_t tid; return 0; }"
  c11_thread
  )
endif()
