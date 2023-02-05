set_property(DIRECTORY PROPERTY LABELS C11)

# --- static assert
check_source_compiles(C
[=[
#include <assert.h>
int main(void) { static_assert(0==0, ""); return 0; }
]=]
c11_static_assert
)
if(c11_static_assert)
  add_executable(static_assert static_assert.c)
  add_test(NAME StaticAssert COMMAND static_assert)
endif()

# --- Generic
file(READ generic.c _src)
check_source_compiles(C "${_src}" c11_generic)

if(c11_generic)
  add_executable(generic generic.c)
  add_test(NAME Generic COMMAND generic)
endif()

# --- C11 noreturn
check_source_compiles(C
[=[
#include <stdlib.h>
#include <stdnoreturn.h>

noreturn void f(){ exit(0); }
int main(void) { f(); }
]=]
c11_noreturn
)

if(c11_noreturn)
  add_executable(C11_noreturn noreturn.c)
  add_test(NAME C11_noreturn COMMAND C11_noreturn)
endif()

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
