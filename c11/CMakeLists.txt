# --- static assert
check_c_source_compiles("
#include <assert.h>
int main(void) { static_assert(0==0, \"\"); return 0; }" c11static_assert)
if(c11static_assert)
  add_executable(static_assert)
  if(WIN32)
    target_sources(static_assert PRIVATE static_assert_windows.c)
  else()
    target_sources(static_assert PRIVATE static_assert.c)
  endif()
endif()

# --- Generic
file(READ generic.c _src)

set(CMAKE_REQUIRED_FLAGS)
if(MSVC)
  set(CMAKE_REQUIRED_FLAGS "/std:c11")
endif()
check_c_source_compiles("${_src}" c11generic)

if(c11generic)
  add_executable(generic generic.c)
  target_compile_features(generic PRIVATE c_std_11)
endif()
# ---
