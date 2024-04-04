#if !__has_c_attribute(noreturn)
#error "no noreturn attribute"
#endif

#include <stdlib.h>

[[ noreturn ]] void f(){ exit(0); }

int main(void) {
  f();
  return EXIT_FAILURE;
}
