#include <stdio.h>
#include <stdlib.h>

int main(void){

  int n = 2;

  switch (n) {
    case 1:
      printf("one\n");
      break;
    case 2:
      printf("two\n");
      [[fallthrough]];
    case 3:
      printf("three\n");
      [[fallthrough]];
    default:
      printf("default\n");
  }

  return EXIT_SUCCESS;
}
