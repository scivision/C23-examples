#include <stdio.h>
#include <stdlib.h>

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

  char* name = "PATH";

  char* buf;
  buf = getenv(name);
  if(!buf){
    fprintf(stderr, "ERROR:getenv\n");
    return EXIT_FAILURE;
  }

  printf("%s: %s\n", name, buf);

  return EXIT_SUCCESS;
}
