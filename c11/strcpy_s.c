// https://en.cppreference.com/w/c/string/byte/strcpy
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main(void)
{
    char *src = "Take the test.";
//  src[0] = 'M' ; // this would be undefined behavior
    char dst[14 + 1]; // +1 to accomodate for the null terminator

    errno_t r = strcpy_s(dst, sizeof dst, src);
    assert(r == 0);
    assert(strcmp(dst, src) == 0);
    r = strcpy_s(dst, sizeof dst, "This intentionally fails because it's too long for 'dst'.");
    assert(r != 0);

    return EXIT_SUCCESS;

}
