#include <malloc.h> 
#include <pthread.h> 

struct job { 
    /* Link field for linked list. */ 
    struct job* next; 
    /* Other fields describing work to be done... */
    char file_name[40];
}; 

/* A linked list of pending jobs. */ 
struct job* job_queue; 

/* A mutex protecting job_queue. */ 
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER; 

// Se crea una funcion donde se ejecuta el trabajo que realiza cada thread
void* process_job (void* arg) 
{
    struct job* current_job = (struct job*) arg;
    sprintf(current_job->file_name, "thread_name:%ld" , (long)pthread_self()); 
    printf ("%s\n" , current_job->file_name);

    return NULL;
}

/* Process queued jobs until the queue is empty. */ 
void* thread_function (void* arg) 
{   
    while (1) { 
        struct job* next_job; 
        
        /* Lock the mutex on the job queue. */ 
        pthread_mutex_lock (&job_queue_mutex); 

        /* Now it's safe to check if the queue is empty. */ 
        if (job_queue == NULL) { 
            next_job = NULL; 
        }

        else { 
            /* Get the next available job. */ 
            next_job = job_queue; 
            
            /* Remove this job from the list. */ 
            job_queue = job_queue->next; 
        } 

        /* Unlock the mutex on the job queue because we're done with the 
        queue for now. */ 
        pthread_mutex_unlock (&job_queue_mutex); 

        /* Was the queue empty? If so, end the thread. */ 
        if (next_job == NULL) 
            break; 
        
        /* Carry out the work. */ 
        process_job (next_job); 
        
        /* Clean up. */ 
        free (next_job); 
    } 
    return NULL; 
}

// Se crea main donde se prueba la lista de jobs e imprime cada thread su id
int main ()
{
    pthread_t threads[20];
    int i;

    struct job* prt_queue_head = (struct job*) malloc(sizeof(struct job));
    struct job* prt_queue_next = prt_queue_head;

    for (i = 0; i < 20; i++) {
        struct job* trabajo = (struct job*) malloc(sizeof(struct job));
        prt_queue_next->next = trabajo;
        prt_queue_next = trabajo;
    }

    job_queue = prt_queue_head;

    for (i = 0; i < 20; i++) 
        pthread_create(&(threads[i]), NULL, thread_function, NULL);
    
    for (i = 0; i < 20; ++i) 
        pthread_join (threads[i], NULL);

    return 0;
}