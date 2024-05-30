// https://en.cppreference.com/w/c/language/constexpr

#include <fenv.h>
#include <stdio.h>

#ifdef HAVE_CONSTEXPR
#define CONSTEXPR constexpr
#else
#warning "constexpr is not supported"
#define CONSTEXPR
#endif

int main(void)
{
    CONSTEXPR float f = 23.0f;
    CONSTEXPR float g = 33.0f;
    fesetround(FE_TOWARDZERO);
    CONSTEXPR float h = f / g; // is not affected by fesetround() above
    printf("%f\n", h);
}
