// https://en.cppreference.com/w/c/string/byte/strcpy
#define __STDC_WANT_LIB_EXT1__ 1
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

int main(void)
{
#ifdef _MSC_VER
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

    char *src = "Take the test.";
//  src[0] = 'M' ; // this would be undefined behavior
    char dst[14 + 1]; // +1 to accomodate for the null terminator

    errno_t r = strcpy_s(dst, sizeof dst, src);
    printf("dst = \"%s\", r = %d\n", dst, r);
    assert(r == 0);
    assert(strcmp(dst, src) == 0);

#ifdef __STDC_LIB_EXT1__
    set_constraint_handler_s(ignore_handler_s);
#endif
    r = strcpy_s(dst, sizeof dst, "This intentionally fails because it's too long for 'dst'.");
    assert(r != 0);

    return EXIT_SUCCESS;

}
