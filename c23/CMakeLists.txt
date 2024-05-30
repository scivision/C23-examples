set_property(DIRECTORY PROPERTY LABELS C23)

message(STATUS "C23 configuration checks:")

set(CMAKE_REQUIRED_DEFINITIONS -D__STDC_WANT_LIB_EXT2__=1)

check_symbol_exists(__STDC_ALLOC_LIB__ "stdio.h" c23_alloc)
# https://en.cppreference.com/w/c/experimental/dynamic

check_symbol_exists(unreachable "stddef.h" c23_unreachable)
check_symbol_exists(static_assert "" c23_static_assert)

# GCC >= 7
check_symbol_exists(__has_include "" c23_has_include)

# GCC >= 11
check_symbol_exists(__has_c_attribute "" c23_has_c_attribute)

if(c23_alloc)
  # else false positive from non-POSIX following compilers
  check_symbol_exists(strndup "string.h" c23_strndup)
  check_symbol_exists(strdup "string.h" c23_strdup)
endif()

check_symbol_exists(BOOL_WIDTH "limits.h" c23_limits)

check_source_compiles(C
"int main(void){ auto i = 0; return 0; }"
c23_auto_type
)

# for auto and bool, check_symbol_exists() is not appropriate as they're not symbols in C23che
check_source_compiles(C
"int main(void){ bool b = true; return 0; }"
c23_bool
)

# MSVC 19.39 didn't yet have #warning
check_source_compiles(C
"#warning \"hi\"
int main(void) { return 0; }"
c23_warning
)

if(c23_has_c_attribute)

check_source_compiles(C
"#if !__has_c_attribute(fallthrough)
#error \"no fallthrough attribute\"
#endif
int main(){ return 0; }"
c23_fallthrough
)

check_source_compiles(C
"#if !__has_c_attribute(noreturn)
#error \"no noreturn attribute\"
#endif
int main(){ return 0; }"
c23_noreturn
)

check_source_compiles(C
"#if !__has_c_attribute(maybe_unused)
#error \"no maybe_unused attribute\"
#endif
int main(){ return 0; }"
c23_maybe_unused
)

if(c23_warning)
check_source_compiles(C
"#if !__has_c_attribute(reproducible)
#error \"no reproducible attribute\"
#endif
int main(){ return 0; }"
c23_reproducible
)

# https://en.cppreference.com/w/c/compiler_support/23
check_source_compiles(C
"#if !__has_c_attribute(unsequenced)
#error \"no unsequenced attribute\"
#endif
int main(){ return 0; }"
c23_unsequenced
)
endif()

endif()

check_source_compiles(C
"#ifdef N
#elifdef M
#elifndef Y
#endif
int main(void) { return 0; }"
c23_elifdef
)

if(c23_warning)
# https://en.cppreference.com/w/c/language/constexpr
check_source_compiles(C
"int main(void){
  constexpr int i = 0;
  return i;
}"
c23_constexpr
)
endif()

check_source_compiles(C
"#include <stddef.h>
int main(void){ int i = nullptr; return 0; }"
c23_nullptr
)

set(f23 bool has_c_attribute has_include
fallthrough maybe_unused noreturn nullptr
strdup strndup
constexpr limits reproducible unsequenced
unreachable
)

foreach(t IN LISTS f23)
  if(c23_${t})
    add_executable(${t} ${t}.c)
    if(NOT t STREQUAL unreachable)
      add_test(NAME ${t} COMMAND ${t})
    endif()
  endif()
endforeach()

if(c23_constexpr)
target_link_libraries(constexpr PRIVATE $<$<BOOL:${UNIX}>:m>)
target_compile_definitions(constexpr PRIVATE $<$<BOOL:${c23_constexpr}>:HAVE_CONSTEXPR>)
set_property(TEST constexpr PROPERTY PASS_REGULAR_EXPRESSION "0.6969")
endif()

if(c23_unreachable)
  add_test(NAME unreachable
  COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:unreachable> -P ${PROJECT_SOURCE_DIR}/cmake/will_fail.cmake
  )
  set_tests_properties(unreachable PROPERTIES WILL_FAIL TRUE)
endif()


# --- count features enabled
get_property(t DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
list(LENGTH f23 Nf)
list(LENGTH t Ne)
message(STATUS "C23 features: ${Ne} / ${Nf}")
if(Ne LESS Nf)
  message(STATUS "enabled targets: ${t}")
endif()
