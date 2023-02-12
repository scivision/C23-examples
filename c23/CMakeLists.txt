set_property(DIRECTORY PROPERTY LABELS C23)

check_source_compiles(C
"int main(void){ auto i = 0; return 0; }"
c23_auto_type
)

# --- strndup
# https://en.cppreference.com/w/c/experimental/dynamic
check_symbol_exists(__STDC_ALLOC_LIB__ "stdio.h" c23_alloc)

file(READ strndup.c _src)
check_source_compiles(C "${_src}" c23_strndup)

if(c23_strndup)
  add_executable(strndup strndup.c)
  add_test(NAME strndup COMMAND strndup)
endif()

# --- strdup

file(READ strdup.c _src)
check_source_compiles(C "${_src}" c23_strdup)

if(c23_strdup)
  add_executable(strdup strdup.c)
  add_test(NAME strdup COMMAND strdup)
endif()

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
"[[ maybe_unused ]] void f(){ }
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
int main(void) { f(); }"
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
check_source_compiles(C
"#include <stddef.h>
int main(void){ unreachable(); return 0; }"
c23_unreachable
)

#  C11 fallback for some compilers
if(c23_unreachable OR CMAKE_C_COMPILER_ID MATCHES "Clang|GNU|Intel|MSVC")
  add_executable(unreachable unreachable.c)
  target_compile_definitions(unreachable PRIVATE
  $<$<BOOL:${c23_unreachable}>:c23_unreachable>
  $<$<BOOL:${c23_fallthrough}>:c23_fallthrough>
  )
  add_test(NAME unreachable
  COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:unreachable> -P ${PROJECT_SOURCE_DIR}/cmake/will_fail.cmake
  )
  set_property(TEST unreachable PROPERTY WILL_FAIL TRUE)
endif()

# --- C23 bool
check_source_compiles(C "int main(void){ bool b = true; return 0; }"
c23_bool
)
