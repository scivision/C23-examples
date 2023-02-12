#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char name[L_tmpnam_s];
    errno_t r = tmpnam_s(name, L_tmpnam_s);

    if(r != 0){
        fprintf(stderr, "failed to get temp file name\n");
        return EXIT_FAILURE;
    }

    printf("temporary file name: %s\n", name);
}
