// https://en.cppreference.com/w/c/string/byte/strndup

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
