// https://stackoverflow.com/a/76847906

#if !__has_c_attribute(reproducible)
#error "no [[reproducible]] attribute"
#endif

#include <stdio.h>
#include <stdlib.h>

[[reproducible]]
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
