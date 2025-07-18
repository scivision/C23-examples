set_property(DIRECTORY PROPERTY LABELS C23)

set(CMAKE_C_STANDARD 23)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# speeds testing up to 2x

check_symbol_exists(unreachable "stddef.h" c23_unreachable)
check_symbol_exists(static_assert "" c23_static_assert)

# GCC >= 7
check_symbol_exists(__has_include "" c23_has_include)

# GCC >= 11
check_symbol_exists(__has_c_attribute "" c23_has_c_attribute)

check_symbol_exists(strndup "string.h" c23_strndup)
check_symbol_exists(strdup "string.h" c23_strdup)

check_symbol_exists(BOOL_WIDTH "limits.h" c23_limits)


# for auto and bool, check_symbol_exists() is not appropriate as they're not symbols in C23che
check_source_compiles(C "auto i = 0;" c23_auto_type)
check_source_compiles(C "bool b = true;" c23_bool)

if(NOT DEFINED c23_warning)
  try_compile(c23_warning SOURCE_FROM_CONTENT "main.c" "#warning \"hello\"")
endif()

if(c23_has_c_attribute)
# https://en.cppreference.com/w/c/compiler_support/23

foreach(a IN ITEMS fallthrough maybe_unused nodiscard noreturn reproducible unsequenced)
  check_source_compiles(C
  "#if !__has_c_attribute(${a})
  #error \"no ${a} attribute\"
  #endif"
  c23_${a}
  )
endforeach()

endif()

check_source_compiles(C
"#ifdef N
#elifdef M
#elifndef Y
#endif"
c23_elifdef
)

# https://en.cppreference.com/w/c/language/constexpr
check_source_compiles(C "constexpr int i = 0;" c23_constexpr)

check_source_compiles(C
"#include <stddef.h>
nullptr_t p = nullptr;"
c23_nullptr
)

# CTest setup

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
  set_property(TEST constexpr PROPERTY PASS_REGULAR_EXPRESSION "0.6969")
endif()

if(c23_unreachable)
  add_test(NAME unreachable
  COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:unreachable> -P ${PROJECT_SOURCE_DIR}/cmake/will_fail.cmake
  )
  set_tests_properties(unreachable PROPERTIES WILL_FAIL TRUE)
endif()
