#include <stdio.h>
#include <stdlib.h>
#include "reciprocal.hpp"
int main (int argc, char **argv)
{
    int i;
    //si no se pasaron argumentos usar numero aleatorio entre 1 y 10
    if(argc == 2) {
        i = atoi (argv[1]);
    } else {
        printf("Por favor pasar un número como argumento\n");
        printf("Usando número aleatorio...\n");
        i = rand() % 100 + 1;
    }
    printf ("The reciprocal of %d is %g\n", i, reciprocal (i));
    return 0;
}