set_property(DIRECTORY PROPERTY LABELS C99)

message(STATUS "C99 configuration checks:")

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

if(c99_restrict)
  add_executable(restrict restrict.c)
  add_test(NAME restrict COMMAND restrict)
endif()

# --- designated
check_source_compiles(C
"int main(void){ int a[2] = { [1] = 3 }; return 0; }"
c99_designated)

if(c99_designated)
  add_executable(designated designated.c)
  add_test(NAME designated COMMAND designated)
endif()
