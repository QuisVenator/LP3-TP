#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

#define KEY 14921
union semun
{
    int val;
    struct semid_ds * buf;
    unsigned short int *array;
    struct seminfo *__buf;
};

/* Obtain a binary sem id allocating if necesary */

int binary_semaphore_allocation (key_t key, int sem_flags){
    return semget(key,1,sem_flags);
}

/*Dealocate a binary semaphore. All users must have finished their use. Returns -1 if on failure*/
int binary_semaphore_deallocate(int semid){
    union semun ignored_argument;
    return semctl(semid,1,IPC_RMID, ignored_argument);
}

int main(){
    int semid = binary_semaphore_allocation(KEY,IPC_CREAT);
    int dealoc;
    if (semid == -1)
    {
        printf("failed to allocate a semaphore\n");
    }else{
        printf("semaphore allocated with KEY %d\n",KEY);

        printf("Dealocating semaphore with semid : %d\n", semid); 
        dealoc = binary_semaphore_deallocate(semid);
        if (dealoc != -1)
        {
            printf("semaphore dealocated successfully\n");
        }else{
            printf("failed to dealocate semaphore\n");
        }
    }  
}