if(MSVC AND CMAKE_VERSION VERSION_LESS 3.19)
  message(STATUS "Visual Studio requires CMake >= 3.19 for C11")
  return()
endif()

set(CMAKE_REQUIRED_FLAGS)
if(MSVC)
  set(CMAKE_REQUIRED_FLAGS "/std:c11")
endif()

# --- static assert
check_c_source_compiles("
#include <assert.h>
int main(void) { static_assert(0==0, \"\"); return 0; }" c11static_assert)
if(c11static_assert)
  add_executable(static_assert)
  target_compile_features(static_assert PRIVATE c_std_11)
  if(WIN32)
    target_sources(static_assert PRIVATE static_assert_windows.c)
  else()
    target_sources(static_assert PRIVATE static_assert.c)
  endif()
endif()

# --- Generic
file(READ generic.c _src)
check_c_source_compiles("${_src}" c11generic)

if(c11generic)
  add_executable(generic generic.c)
  target_compile_features(generic PRIVATE c_std_11)
endif()
# --- variable length array
check_c_source_compiles("int main(void){for (int i = 1; i < 5; i++){int a[i];} return 0;}" c11vla)
if(c11vla)
  add_executable(vla vla.c)
  target_compile_features(vla PRIVATE c_std_11)
  add_test(NAME VariableLengthArray COMMAND $<TARGET_FILE:vla> 3)
  set_tests_properties(VariableLengthArray PROPERTIES
    PASS_REGULAR_EXPRESSION "^1 2 3[ \t\r\n]+$")
endif()
# --- threading
check_c_source_compiles("#include <threads.h>
int main(void){ thrd_t tid; return 0; }" c11thread)
