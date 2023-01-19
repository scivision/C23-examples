set_property(DIRECTORY PROPERTY LABELS C23)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
  set(CMAKE_REQUIRED_FLAGS "-Werror")
endif()

check_source_compiles(C
"int main(void){ int i = nullptr; return 0; }"
c23nullptr)

check_source_compiles(C
[=[
#include <stdlib.h>

[[ noreturn ]] void f(){ exit(0); }
int main() { f(); }
]=]
c23no_return
)

check_source_compiles(C "int main(void){ bool b = true; return 0; }"
c23bool
)

if(c23nullptr)
  add_executable(nullptr nullptr.c)
endif()

if(c23no_return)
  add_executable(no_return no_return.c)
endif()
