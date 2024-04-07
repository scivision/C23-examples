// https://stackoverflow.com/a/76847906

#ifdef __has_c_attribute
#if __has_c_attribute(unsequenced)
#define UNSEQ [[unsequenced]]
#endif
#endif
#ifndef UNSEQ
#if defined(__GNUC__) || defined(__clang__)
#ifdef HAVE_WARNING
#warning "substituting attribute const for unsequenced"
#endif
#define UNSEQ __attribute__ ((const))
#else
#ifdef HAVE_WARNING
#warning "unsequenced attribute not supported"
#endif
#define UNSEQ
#endif
#endif

#include <stdio.h>
#include <stdlib.h>

UNSEQ
int sum(int a, int b){
    return a + b;
}

int main(){
    int a = 1;
    int b = 2;

    int c = sum(a, b);
    c = sum(a+1, b);
    c = sum(a, b);

    printf("%d\n", c);

    if(c != 3)
      return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
