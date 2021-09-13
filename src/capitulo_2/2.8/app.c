#include "app.h"
int main ()
{
    int aux = f ();
    printf("Función f retorna: %d\n", aux);
    return f ();
}