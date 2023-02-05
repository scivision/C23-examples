// C11 variable length array

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

int j = 5;
if (argc == 2) j = atoi(argv[1]);

for (int i = 1; i <= j; i++){
   int a[i]; // re-allocated each iteration
   printf("%zu ", sizeof a / sizeof *a);
}

return EXIT_SUCCESS;

}
