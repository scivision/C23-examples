set_property(DIRECTORY PROPERTY LABELS C11)

message(STATUS "C11 configuration checks:")

# don't check __STDC_NO_VLA__  __STDC_NO_THREADS__
# as you need a try_run() to read the macro values.
# faster to just check_source_compiles() a minimal test program.
check_symbol_exists(static_assert "assert.h" c11_static_assert)

# --- Generic
file(READ generic.c _src)
check_source_compiles(C "${_src}" c11_generic)


# --- C11 noreturn
# deprecated by [[noreturn]] in C23
# https://en.cppreference.com/w/c/language/_Noreturn
check_source_compiles(C
"#include <stdlib.h>
#include <stdnoreturn.h>
noreturn void f(){ exit(0); }
int main(void) { f(); return EXIT_FAILURE; }"
c11_noreturn
)

foreach(t IN ITEMS generic noreturn static_assert)
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

# --- threading (typically not supported)
check_include_file(threads.h c11_thread_h)
if(c11_thread_h)
  check_source_compiles(C
  "#include <threads.h>
  int main(void){ thrd_t tid; return 0; }"
  c11_thread
  )
endif()
