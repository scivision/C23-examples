check_c_source_compiles("int main(void){ int* restrict a; return 0; }" c99restrict)

if(c99restrict)
  add_executable(restrict restrict.c)
  target_compile_features(restrict PRIVATE c_std_99)
endif()


check_c_source_compiles("int main(void){ int a[2] = { [1] = 3 }; return 0; }" c99designated)

if(c99designated)
  add_executable(designated designated.c)
  target_compile_features(designated PRIVATE c_std_99)
endif()
