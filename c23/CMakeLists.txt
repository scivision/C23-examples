set_property(DIRECTORY PROPERTY LABELS C23)

message(STATUS "C23 configuration checks:")

set(CMAKE_REQUIRED_DEFINITIONS -D__STDC_WANT_LIB_EXT2__=1)

check_symbol_exists(__STDC_ALLOC_LIB__ "stdio.h" c23_alloc)
check_symbol_exists(unreachable "stddef.h" c23_unreachable)
check_symbol_exists(static_assert "" c23_static_assert)


if(c23_alloc)
  # else false positive from non-POSIX following compilers
  check_symbol_exists(strndup "string.h" c23_strndup)
  check_symbol_exists(strdup "string.h" c23_strdup)
endif()

check_source_compiles(C
"int main(void){ auto i = 0; return 0; }"
c23_auto_type
)

# --- strndup, strdup
# https://en.cppreference.com/w/c/experimental/dynamic
foreach(t IN ITEMS strdup strndup)
  if(c23_${t})
    add_executable(C23_${t} ${t}.c)
    add_test(NAME C23_${t} COMMAND C23_${t})
  endif()
endforeach()

# --- C23 nullptr
check_source_compiles(C
"#include <stddef.h>
int main(void){ int i = nullptr; return 0; }"
c23_nullptr)

if(c23_nullptr)
  add_executable(nullptr nullptr.c)
  add_test(NAME nullptr COMMAND nullptr)
endif()

# --- C23 maybe_unused
check_source_compiles(C
"[[ maybe_unused ]] void f(){ [[ maybe_unused ]] int i; }
int main(void) { return 0; }"
c23_maybe_unused
)
if(c23_maybe_unused)
  add_executable(maybe_unused maybe_unused.c)
  add_test(NAME maybe_unused COMMAND maybe_unused)
endif()

# --- C23 noreturn

check_source_compiles(C
"#include <stdlib.h>
[[ noreturn ]] void f(){ exit(0); }
int main(void) { f(); return EXIT_FAILURE; }"
c23_noreturn
)

if(c23_noreturn)
  add_executable(C23_noreturn noreturn.c)
  add_test(NAME C23_noreturn COMMAND C23_noreturn)
endif()

# --- C23 fallthrough

check_source_compiles(C
"int main(void){
  switch (0) {
    case 1:
    case 2:
     [[fallthrough]];
    case 3:
  }
  return 0;
}"
c23_fallthrough
)
if(c23_fallthrough)
  add_executable(fallthrough fallthrough.c)
  add_test(NAME fallthrough COMMAND fallthrough)
endif()

# --- unreachable

if(c23_unreachable)
  add_executable(C23_unreachable unreachable.c)
  target_compile_definitions(C23_unreachable PRIVATE $<$<BOOL:${c23_fallthrough}>:c23_fallthrough>)
  add_test(NAME C23_unreachable
  COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:C23_unreachable> -P ${PROJECT_SOURCE_DIR}/cmake/will_fail.cmake
  )
  set_property(TEST C23_unreachable PROPERTY WILL_FAIL TRUE)
endif()

# --- C23 bool
check_source_compiles(C "int main(void){ bool b = true; return 0; }"
c23_bool
)
