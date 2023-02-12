// https://en.cppreference.com/w/c/experimental/dynamic/strndup
#ifdef __STDC_ALLOC_LIB__ // C23
#define __STDC_WANT_LIB_EXT2__ 1
#else // pre-C23 via GNU extensions
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
}
