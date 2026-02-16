set_property(DIRECTORY PROPERTY LABELS C99)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# speeds testing up to 2x

set(CMAKE_REQUIRED_DEFINITIONS -D_GNU_SOURCE)

check_symbol_exists(secure_getenv "stdlib.h" HAVE_SECURE_GETENV)

add_executable(getenv getenv.c)
target_compile_definitions(getenv PRIVATE $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)
add_test(NAME getenv COMMAND getenv)

# --- restrict keyword
check_source_compiles(C
"int main(void){ int* restrict a; return 0; }"
c99_restrict)

# --- designated
check_source_compiles(C
"int main(void){ int a[2] = { [1] = 3 }; return 0; }"
c99_designated)


foreach(t IN LISTS c99features)
  if(c99_${t})
    add_executable(${t} ${t}.c)
    add_test(NAME ${t} COMMAND ${t})
  endif()
endforeach()

if(TARGET restrict)
  target_compile_options(restrict PRIVATE $<$<C_COMPILER_ID:GNU>:-Wno-dangling-pointer>)
endif()
