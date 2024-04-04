// https://en.cppreference.com/w/c/language/attributes/maybe_unused

#if !__has_c_attribute(maybe_unused)
#error "no maybe_unused attribute"
#endif

#ifndef bool
// GCC < 13, Clang < 15
#include <stdbool.h>
#endif

#include <assert.h>

#include <stdlib.h>
#include <stdio.h>

[[maybe_unused]] void f([[maybe_unused]] bool cond1, [[maybe_unused]] bool cond2)
{
   [[maybe_unused]] bool b = cond1 && cond2;
   assert(b);
   // in release mode, assert is compiled out, and b is unused
   // no warning because it is declared [[maybe_unused]]
} // parameters cond1 and cond2 are not used, no warning

int main(void)
{
  f(1, 1);

  printf("OK: maybe_unused\n");
  return EXIT_SUCCESS;
}
