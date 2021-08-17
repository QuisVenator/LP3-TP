#include <malloc.h>
#include <pthread.h>
#include <stdlib.h>

/* Allocate a temporary buffer. */
void* allocate_buffer (size_t size)
{
    return malloc (size);
}

/* Deallocate a temporary buffer. */
void deallocate_buffer (void* buffer)
{
    printf("Deallocando buffer\n");
    free (buffer);
}

void* do_some_work (void* arg)
{
    /* Allocate a temporary buffer. */
    void* temp_buffer = allocate_buffer (1024);

    /* Register a cleanup handler for this buffer, to deallocate it in
    case the thread exits or is cancelled. */
    pthread_cleanup_push (deallocate_buffer, temp_buffer);

    /* Do some work here that might call pthread_exit or might be
    cancelled... */
    fflush(stdout);
    if(random() < RAND_MAX/2) {
        printf("Hilo fue cancelado\n");
        pthread_exit(0);
    }
    printf("Hilo no fue cancelado\n");

    /* Unregister the cleanup handler. Because we pass a nonzero value,
    this actually performs the cleanup by calling
    deallocate_buffer. */
    pthread_cleanup_pop (1);
}

int main() {
    printf("Se crean 10 threads, cada uno tiene probabilidad de aproximadmente "
        "50%% de llamar pthread_exit(), igual todos llaman cleanup.\n\n");

    //lanzar unos cuantos threads para que ojala algunos se cancelen y otros no thread
    pthread_t thread[10];
    for(int i = 0; i < 10; i++) {
        pthread_create (&thread[i], NULL, &do_some_work, NULL);
    }

    //cerrar todos los threads
    for(int i = 0; i < 10; i++) {
        pthread_join (thread[i], NULL);
    }
}