#include <malloc.h>
#include <stdio.h>
#include <string.h>
 
struct job {
  /* Link field for linked list.  */
  char name[20];
  struct job* next;
 
  /* Other fields describing work to be done... */
};
 
/* A linked list of pending jobs.  */
struct job* job_queue;
 
void process_job (struct job* trabajo){
    printf("Procesando tarea %s\n", trabajo->name);
}
 
/* Process queued jobs until the queue is empty.  */
 
void* thread_function (void* arg)
{
  while (job_queue != NULL) {
    /* Get the next available job.  */
    struct job* next_job = job_queue;
    /* Remove this job from the list.  */
    job_queue = job_queue->next;
    /* Carry out the work.  */
    process_job (next_job);
    /* Clean up.  */
    free (next_job);
  }
  return NULL;
}
 
struct job* trabajo1;
struct job* trabajo2;
struct job* trabajo3;
 
int main(int argc, char **argv){
    trabajo1 = malloc(sizeof(struct job));
    trabajo2 = malloc(sizeof(struct job));
    trabajo3 = malloc(sizeof(struct job));
 
    strcpy(trabajo1->name, "trabajo1");
    strcpy(trabajo2->name, "trabajo2");
    strcpy(trabajo3->name, "trabajo3");
 
    trabajo1->next = trabajo2;
    trabajo2->next = trabajo3;
    trabajo3->next = NULL;
 
 
    job_queue = trabajo1;
 
    thread_function(NULL);
    return 0;
}