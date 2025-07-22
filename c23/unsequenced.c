// https://stackoverflow.com/a/76847906

#include <stdio.h>
#include <stdlib.h>


int sum(int a, int b)
[[unsequenced]]
{
    return a + b;
}

int main(){
    int a = 1;
    int b = 2;

    int c = sum(a, b);
    c = sum(a+1, b);
    c = sum(a, b);

    if(c != 3){
      fprintf(stderr, "Error: expected 3, got %d\n", c);
      return EXIT_FAILURE;
    }

    printf("OK: %d\n", c);
    return EXIT_SUCCESS;
}
