#include <stdlib.h>
#include <stdio.h>

// Se crea para ejecutar de manera automatica sin cargar argumentos
int main () {
    int estado = system("./socket-inet www.google.com");

    if (estado >= 0) {
        printf("\nEjecutado con exito\n");
    }
    else {
        printf("\nError en la ejecucion: %d\n", estado);
    }

    return 0;
}