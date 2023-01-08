set_property(DIRECTORY PROPERTY LABELS C23)

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

if(c23nullptr)
  add_executable(nullptr nullptr.c)
endif()

if(c23no_return)
  add_executable(no_return no_return.c)
endif()
