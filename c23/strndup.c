// https://en.cppreference.com/w/c/string/byte/strndup

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#warning "C23 strndup not available. Falling back to POSIX strndup."
#define _POSIX_C_SOURCE 200809L
#endif


#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main(void)
{
    const char *s1 = "String";
    char *s2 = strndup(s1, 2);
    assert(strcmp(s2, "St") == 0);
    free(s2);

    return EXIT_SUCCESS;
}
