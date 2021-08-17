#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "job-queue3.h"

/* A linked list of pending jobs. */
struct job* job_queue;
/* A mutex protecting job_queue. */
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;

/* A semaphore counting the number of jobs in the queue. */
sem_t job_queue_count;

int main() {
    // crear 5 threads de trabajo
    pthread_t thread_ids[5];
    for(int i = 0; i < 5; i++) {
        pthread_create(&thread_ids[i],NULL,thread_function,NULL);
    }

    printf("5 Threads creados, 5 trabajos creados\n"
    "Desupues esperar unos segundos para crear 10 nuevos trabajos.\n\n");
    fflush(stdout);

    //crear 10 trabajos
    for(int i = 0; i < 5; i++)
        enqueue_job();
    
    sleep(3);

    //crear 10 trabajos
    for(int i = 0; i < 10; i++)
        enqueue_job();
    
    //esperar que semforo vuelva a ser 0
    int trabajos_pendiente;
    do {
        sem_getvalue(&job_queue_count, &trabajos_pendiente);
    } while(trabajos_pendiente);

    //dar un poco de tiempo para que se muestren los prints
    sleep(5);
    return 0;
}

/* Perform one-time initialization of the job queue. */
void initialize_job_queue ()
{
    /* The queue is initially empty. */
    job_queue = NULL;
    /* Initialize the semaphore which counts jobs in the queue. Its
    initial value should be zero. */
    sem_init (&job_queue_count, 0, 0);
}

/* Process queued jobs until the queue is empty. */
void* thread_function (void* arg)
{
    while (1) {
        struct job* next_job;
        /* Wait on the job queue semaphore. If its value is positive,
        indicating that the queue is not empty, decrement the count by
        1. If the queue is empty, block until a new job is enqueued. */
        sem_wait (&job_queue_count);
        
        /* Lock the mutex on the job queue. */
        pthread_mutex_lock (&job_queue_mutex);

        /* Because of the semaphore, we know the queue is not empty. Get
        the next available job. */
        next_job = job_queue;

        /* Remove this job from the list. */
        job_queue = job_queue->next;

        /* Unlock the mutex on the job queue because we're done with the
        queue for now. */
        pthread_mutex_unlock (&job_queue_mutex);

        /* Carry out the work. */
        process_job (next_job);

        /* Clean up. */
        free (next_job);
    }

    return NULL;
}

/* Add a new job to the front of the job queue. */
void enqueue_job (/* Pass job-specific data here... */)
{
    struct job* new_job;

    /* Allocate a new job object. */
    new_job = (struct job*) malloc (sizeof (struct job));
    /* Set the other fields of the job struct here... */
    new_job->num = rand();

    /* Lock the mutex on the job queue before accessing it. */
    pthread_mutex_lock (&job_queue_mutex);

    /* Place the new job at the head of the queue. */
    new_job->next = job_queue;
    job_queue = new_job;
    
    /* Post to the semaphore to indicate that another job is available. If
    threads are blocked, waiting on the semaphore, one will become
    unblocked so it can process the job. */
    sem_post (&job_queue_count);
    
    /* Unlock the job queue mutex. */
    pthread_mutex_unlock (&job_queue_mutex);
}

void process_job(struct job* job) {
    int max_div = job->num / 2;
    
    if(job->num > 1)
        job->cant_div = 1; //cada numero es divisible por si mismo
    else
        job->cant_div = 0;

    //hallar todos los divisores, no eficiente, ejemplo nomás
    for(int i = 1; i <= max_div; i++) {
        if(job->num % i == 0) job->cant_div++;
    }
    printf("%d tiene %d divisores.\n", job->num, job->cant_div);
    fflush(stdout);
}