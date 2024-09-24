set_property(DIRECTORY PROPERTY LABELS C99)

set(CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)

check_symbol_exists(secure_getenv "stdlib.h" HAVE_SECURE_GETENV)

add_executable(getenv getenv.c)
target_compile_definitions(getenv PRIVATE $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)
add_test(NAME getenv COMMAND getenv)

# can't do check_symbol_exists for built-in functions like __assume and __builtin_unreachable
file(READ unreachable.c _src)
check_source_compiles(C "${_src}" builtin_unreachable)

# --- unreachable compiler extensions
if(builtin_unreachable)
  add_executable(ext_unreachable unreachable.c)
  add_test(NAME ext_unreachable
  COMMAND ${CMAKE_COMMAND} -Dexe:FILEPATH=$<TARGET_FILE:ext_unreachable> -P ${PROJECT_SOURCE_DIR}/cmake/will_fail.cmake
  )
  set_property(TEST ext_unreachable PROPERTY WILL_FAIL TRUE)
endif()

# --- restrict keyword
check_source_compiles(C
"int main(void){ int* restrict a; return 0; }"
c99_restrict)

# --- designated
check_source_compiles(C
"int main(void){ int a[2] = { [1] = 3 }; return 0; }"
c99_designated)


foreach(t IN LISTS c99features)
  if(c99_${t})
    add_executable(${t} ${t}.c)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()
