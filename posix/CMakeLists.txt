set_property(DIRECTORY PROPERTY LABELS posix)

set(CMAKE_REQUIRED_DEFINITIONS -D_POSIX_C_SOURCE=200809L)

check_symbol_exists(strndup "string.h" posix_strndup)

if(posix_strndup)
  add_executable(POSIX_strndup strndup.c)
  add_test(NAME POSIX_strndup COMMAND POSIX_strndup)
endif()
