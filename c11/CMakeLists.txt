set_property(DIRECTORY PROPERTY LABELS C11)

set(CMAKE_C_STANDARD 11)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# speeds testing up to 2x

# don't check __STDC_NO_VLA__  __STDC_NO_THREADS__
# as you need a try_run() to read the macro values.
# faster to just check_source_compiles() a minimal test program.

# --- Generic
file(READ generic.c _src)
check_source_compiles(C "${_src}" c11_generic)


# --- C11 noreturn
# deprecated by [[noreturn]] in C23
# https://en.cppreference.com/w/c/language/_Noreturn
check_source_compiles(C
"#include <stdlib.h>  // for exit()
#include <stdnoreturn.h>
noreturn void f(){ exit(0); }"
c11_c11noreturn
)

check_source_compiles(C
"void f(void) { for (int i = 1; i < 5; i++){int a[i];} }"
c11_vla
)

foreach(t IN LISTS c11features)
  if(c11_${t})
    add_executable(${t} ${t}.c)

    if(c11_vla AND t STREQUAL "vla")
      add_test(NAME VariableLengthArray COMMAND vla 3)
      set_property(TEST VariableLengthArray PROPERTY PASS_REGULAR_EXPRESSION "^1 2 3[ \t\r\n]+$")
    else()
      add_test(NAME C11_${t} COMMAND ${t})
    endif()
  endif()
endforeach()


# --- threading (typically not supported)
check_include_file("threads.h" c11_thread_h)
if(c11_thread_h)
  check_source_compiles(C
  "#include <threads.h>
  thrd_t tid;"
  c11_thread
  )
endif()
