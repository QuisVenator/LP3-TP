#include "app.h"
#include<stdio.h>

int main ()
{
    int aux = f ();
    printf("Función f retorna: %d\n", aux);
    return f ();
}