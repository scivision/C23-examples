set(CMAKE_C_STANDARD 11)  # so that check_Ssource_compiles works

set(CMAKE_REQUIRED_FLAGS)
# --- static assert
check_source_compiles(C
"#include <assert.h>
int main(void) { static_assert(0==0, \"\"); return 0; }" c11static_assert)
if(c11static_assert)
  add_executable(static_assert)
  if(WIN32)
    target_sources(static_assert PRIVATE static_assert_windows.c)
  else()
    target_sources(static_assert PRIVATE static_assert.c)
  endif()
  add_test(NAME StaticAssert COMMAND static_assert)
endif()

# --- Generic
file(READ generic.c _src)
check_source_compiles(C "${_src}" c11generic)

if(c11generic)
  add_executable(generic generic.c)
  add_test(NAME Generic COMMAND generic)
endif()
# --- variable length array
check_source_compiles(C
  "int main(void){for (int i = 1; i < 5; i++){int a[i];} return 0;}"
  c11vla)
if(c11vla)
  add_executable(vla vla.c)
  add_test(NAME VariableLengthArray COMMAND $<TARGET_FILE:vla> 3)
  set_tests_properties(VariableLengthArray PROPERTIES
    PASS_REGULAR_EXPRESSION "^1 2 3[ \t\r\n]+$")
endif()
# --- threading
check_source_compiles(C
"#include <threads.h>
int main(void){ thrd_t tid; return 0; }"
c11thread)
