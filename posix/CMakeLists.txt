set_property(DIRECTORY PROPERTY LABELS posix)

set(CMAKE_REQUIRED_DEFINITIONS -D_POSIX_C_SOURCE=200809L)

check_symbol_exists(strndup "string.h" posix_strndup)
check_symbol_exists(strdup "string.h" posix_strdup)

foreach(t IN ITEMS strdup strndup)
  if(posix_${t})
    add_executable(POSIX_${t} ${t}.c)
    add_test(NAME POSIX_${t} COMMAND POSIX_${t})
  endif()
endforeach()
