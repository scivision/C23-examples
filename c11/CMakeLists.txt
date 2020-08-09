file(READ generic.c _src)
check_c_source_compiles("${_src}" c11generic)

if(c11generic)
  add_executable(generic generic.c)
  target_compile_features(generic PRIVATE c_std_11)
endif()
