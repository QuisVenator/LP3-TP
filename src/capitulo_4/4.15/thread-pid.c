#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 

void* thread_function (void* arg) 
{
    fprintf (stderr, "child thread pid is %d\n", (int) getpid ()); 
    /* Spin forever. */ 
    while (1); 
    return NULL; 
}

int main () 
{
    // Para que muestre los threads que estan corriendo
    int return_value;
    return_value = system ("ps x");

    printf ("Aprete control+c para cerrar (la aplicacion queda en loop)");
    pthread_t thread;
    fprintf (stderr, "main thread pid is %d\n", (int) getpid ());
    pthread_create (&thread, NULL, &thread_function, NULL);

    /* Spin forever. */ 
    while (1);
    
    return return_value; 
}

/*
Los PID salen iguales debido a que luego de la actualizacion de linux 2.4 cambia la forma en que getpid funciona con los threads
asignando solo un PID 
cualquier duda revisar: https://unix.stackexchange.com/questions/364660/are-threads-implemented-as-processes-on-linux/364663
*/
