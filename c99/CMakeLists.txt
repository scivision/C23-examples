if(NOT MSVC OR CMAKE_C_COMPILER_VERSION VERSION_GREATER_EQUAL 19.27)
  add_executable(restrict restrict.c)
  target_compile_features(restrict PRIVATE c_std_99)
endif()

add_executable(designated designated.c)
target_compile_features(designated PRIVATE c_std_99)
