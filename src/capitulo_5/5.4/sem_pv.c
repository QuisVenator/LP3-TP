#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

// Llave para crear el semaforo
key_t key = (key_t) 1337;

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

// Funcion donde imprime el pid del proceso
void* print_id (void* args, int pid) {
    binary_semaphore_wait(*(int*) args);

    // Si es el proceso padre duerme
    if (pid != 0)
        sleep(3);
        
    printf("Process ID: %d\n", pid);
    binary_semaphore_post (*(int*) args);

    return NULL;
}


/*
En este caso de prueba se imprime primero el PID del padre ya que existe un semaforo
por lo que recien de los 3 segundos del sleep puede continuar y el proceso hijo debe
esperar
*/
int main ()
{
    int semid;
    int new_sem;
    pid_t child_pid;

    // Inicializacion del semaforo
    semid = semget(key, 1, IPC_CREAT | 0777);
    new_sem = binary_semaphore_initialize(semid);
    if (new_sem < 0) {
        perror("Falla al inicializar el semaforo");
        return -1;
    }

    child_pid = fork();

    print_id (&semid, child_pid);
 
    return 0;
}