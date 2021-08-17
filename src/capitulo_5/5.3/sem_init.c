#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 1492

/* We must define union semun ourselves.  */

union semun {
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

int main(){
    printf("Inicializando semaforo binario...\n");
    int semid = semget(KEY, 1, 0666 | IPC_CREAT);
    int semaforo = binary_semaphore_initialize(semid);
    if(semaforo >= 0){
      printf("Semaforo binario inicializado: %d\n",KEY);
    }else{
      printf("No pudo inicializarce: %d\n",errno);
    }
    
    return 0;
}