// https://stackoverflow.com/a/76847906

#ifdef __has_c_attribute
#if __has_c_attribute(reproducible)
#define REPROD [[reproducible]]
#endif
#endif
#ifndef REPROD
#if defined(__GNUC__) || defined(__clang__)
#warning "substituting attribute pure for reproducible"
#define REPROD __attribute__ ((pure))
#else
#warning "reproducible attribute not supported"
#define REPROD
#endif
#endif

#include <stdio.h>
#include <stdlib.h>

REPROD
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
