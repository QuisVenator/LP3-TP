#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <errno.h>
#include <stdio.h>
#include <pthread.h>

// Llave para crear el semaforo
#define KEY 1492

// Variable global
int num;

/* Wait on a binary semaphore. Block until the semaphore value is positive, 
then decrement it by 1. */ 
int binary_semaphore_wait (int semid) 
{ 
    struct sembuf operations[1]; 
    /* Use the first (and only) semaphore. */ 
    operations[0].sem_num = 0; 
    /* Decrement by 1. */ 
    operations[0].sem_op = -1; 
    /* Permit undo'ing. */ 
    operations[0].sem_flg = SEM_UNDO; 
    return semop (semid, operations, 1); 
}

/* Post to a binary semaphore: increment its value by 1. 
 This returns immediately. */ 
int binary_semaphore_post (int semid) 
{ 
    struct sembuf operations[1]; 

    /* Use the first (and only) semaphore. */ 
    operations[0].sem_num = 0; 
    
    /* Increment by 1. */ 
    operations[0].sem_op = 1; 
    
    /* Permit undo'ing. */ 
    operations[0].sem_flg = SEM_UNDO; 

    return semop (semid, operations, 1); 
}

// Parte del codigo para tener las funciones de inicializacion del semaforo 

/* We must define union semun ourselves.  */
union semun 
{
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo *__buf;
};

/* Initialize a binary semaphore with a value of one.  */
int binary_semaphore_initialize (int semid)
{
  union semun argument;
  unsigned short values[1];
  values[0] = 1;
  argument.array = values;
  return semctl (semid, 0, SETALL, argument);
}

// Funcion donde cada thread modifica un valor compartido y lo imprime
void* thread_function (void* args) {
    binary_semaphore_wait(*(int*) args);
    num = (int) pthread_self ();
    printf("Thread ID: %d\n", num);
    binary_semaphore_post (*(int*) args);

    return NULL;
}

int main ()
{
    pthread_t threads[10];
    int i = 0;

    // Inicializacion del semaforo
    int semid = semget(KEY, 1, IPC_CREAT);
    int new_sem = binary_semaphore_initialize(semid);
    if (new_sem < 0) {
        perror("Falla al inicializar el semaforo");
        return -1;
    }   

    // Creacion de los threads
    for (i = 0; i < 10; i++) {
        if(pthread_create(&threads[i], NULL, &thread_function, &semid) != 0)
            perror("Error al crear el thread");
    }
    
    // Hace esperar a los threads
    for (i = 0; i < 10; i++)
        if (pthread_join(threads[i], NULL) != 0)
            perror("Error hacer join");

    return 0;
}