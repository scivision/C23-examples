set_property(DIRECTORY PROPERTY LABELS C23)

set(CMAKE_C_STANDARD 23)

check_symbol_exists(unreachable "stddef.h" c23_unreachable)
check_symbol_exists(static_assert "" c23_static_assert)

# GCC >= 7
check_symbol_exists(__has_include "" c23_has_include)

# GCC >= 11
check_symbol_exists(__has_c_attribute "" c23_has_c_attribute)

check_symbol_exists(strndup "string.h" c23_strndup)
check_symbol_exists(strdup "string.h" c23_strdup)

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

block()

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# MSVC 19.39 didn't yet have #warning
check_source_compiles(C "#warning \"hi\"" c23_warning)

if(c23_has_c_attribute)

check_source_compiles(C
"#if !__has_c_attribute(fallthrough)
#error \"no fallthrough attribute\"
#endif"
c23_fallthrough
)

check_source_compiles(C
"#if !__has_c_attribute(noreturn)
#error \"no noreturn attribute\"
#endif"
c23_noreturn
)

check_source_compiles(C
"#if !__has_c_attribute(maybe_unused)
#error \"no maybe_unused attribute\"
#endif"
c23_maybe_unused
)

check_source_compiles(C
"#if !__has_c_attribute(reproducible)
#error \"no reproducible attribute\"
#endif"
c23_reproducible
)

# https://en.cppreference.com/w/c/compiler_support/23
check_source_compiles(C
"#if !__has_c_attribute(unsequenced)
#error \"no unsequenced attribute\"
#endif"
c23_unsequenced
)

endif()

check_source_compiles(C
"#ifdef N
#elifdef M
#elifndef Y
#endif"
c23_elifdef
)

# https://en.cppreference.com/w/c/language/constexpr
check_source_compiles(C
"int main(void){
  constexpr int i = 0;
  return i;
}"
c23_constexpr
)

endblock()

check_source_compiles(C
"#include <stddef.h>
int main(void){ nullptr_t p = nullptr; return 0; }"
c23_nullptr
)

foreach(t IN LISTS c23features)
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
