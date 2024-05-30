#if __has_include(<stdio.h>)
#include <stdio.h>
#else
#error "Missing <stdio.h>"
#endif

int main(void)
{
    printf("Hello, World!\n");
    return 0;
}
