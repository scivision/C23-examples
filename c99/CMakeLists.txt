add_executable(restrict restrict.c)
target_compile_features(restrict PRIVATE c_std_99)

add_executable(designated designated.c)
target_compile_features(designated PRIVATE c_std_99)
