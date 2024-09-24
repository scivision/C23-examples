#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>

int main(void)
{

  size_t MAXP = 32768;
  size_t L;
  char* name = "PATH";

  char* buf = (char*) malloc(MAXP);

  if(getenv_s(&L, buf, MAXP, name)){
    free(buf);
    fprintf(stderr, "ERROR:getenv\n");
    return EXIT_FAILURE;
  }

  printf("%s: %s\n", name, buf);
  free(buf);
  return EXIT_SUCCESS;
}
