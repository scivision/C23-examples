set(CMAKE_C_STANDARD 99)  # so that check_source_compiles works

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
