set_property(DIRECTORY PROPERTY LABELS C99)

check_source_compiles(C
"int main(void){ int* restrict a; return 0; }"
c99_restrict)

if(c99_restrict)
  add_executable(restrict restrict.c)
  add_test(NAME restrict COMMAND restrict)
endif()


check_source_compiles(C
"int main(void){ int a[2] = { [1] = 3 }; return 0; }"
c99_designated)

if(c99_designated)
  add_executable(designated designated.c)
  add_test(NAME designated COMMAND designated)
endif()
