#include <stdlib.h>
#include <stdio.h>
#include <stdnoreturn.h>

noreturn void f()
{
  printf("noreturn exit(0)\n");
  exit(0);
}

int main(void) {
  f();
  return EXIT_FAILURE;
}
