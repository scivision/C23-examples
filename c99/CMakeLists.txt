set_property(DIRECTORY PROPERTY LABELS C99)

check_source_compiles(C
"int main(void){ int* restrict a; return 0; }"
c99restrict)

if(c99restrict)
  add_executable(restrict restrict.c)
endif()


check_source_compiles(C
"int main(void){ int a[2] = { [1] = 3 }; return 0; }"
c99designated)

if(c99designated)
  add_executable(designated designated.c)
endif()
