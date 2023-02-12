#ifndef __STDC_ALLOC_LIB__
#error "C23 compiler required"
#endif

#define __STDC_WANT_LIB_EXT2__ 1

#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main(void)
{
    const char *s1 = "String";
    char *s2 = strdup(s1);
    assert(strcmp(s1, s2) == 0);
    free(s2);

    return EXIT_SUCCESS;
}
