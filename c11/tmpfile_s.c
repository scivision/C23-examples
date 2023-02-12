#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("TMP_MAX_S = %d, FOPEN_MAX = %d\n", TMP_MAX_S, FOPEN_MAX);

    FILE* tmpf;
    errno_t r = tmpfile_s(&tmpf);
    fclose(tmpf);

    if (r != 0) {
      fprintf(stderr,"tmpfile_s() failed: %d\n", r);
      return EXIT_FAILURE;
    }

    printf("OK: tmpfile_s \n");

    return EXIT_SUCCESS;
}
