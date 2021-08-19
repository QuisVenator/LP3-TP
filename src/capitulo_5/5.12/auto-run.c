#include <stdlib.h>
#include <stdio.h>

int main () {
    int estado = system("./socket-inet www.google.com");

    if (estado >= 0) {
        printf("Ejecutado con exito\n");
    }
    else {
        printf("Error en la ejecucion: %d\n", estado);
    }

    return 0;
}