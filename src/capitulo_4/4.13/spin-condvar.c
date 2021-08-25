#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define waittime 1

void do_work (){
    printf("do work() : Haciendo el trabajo ..\n");
}

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag ()
{
  pthread_mutex_init (&thread_flag_mutex, NULL);
  thread_flag = 0;
}

/* Calls do_work repeatedly while the thread flag is set; otherwise
   spins.  */

void* thread_function (void* thread_arg)
{
  while (1) {
    int flag_is_set;

    /* Protect the flag with a mutex lock.  */
    pthread_mutex_lock (&thread_flag_mutex);
    flag_is_set = thread_flag;
    pthread_mutex_unlock (&thread_flag_mutex);

    if (flag_is_set)
      do_work ();
    /* Else don't do anything.  Just loop again.  */
  }
  return NULL;
}

/* Sets the value of the thread flag to FLAG_VALUE.  */

void set_thread_flag (int flag_value)
{
  /* Protect the flag with a mutex lock.  */
  pthread_mutex_lock (&thread_flag_mutex);
  thread_flag = flag_value;
  pthread_mutex_unlock (&thread_flag_mutex);
}

pthread_t thread_id;

int main(){
  initialize_flag();
  pthread_create(&thread_id, NULL, thread_function, NULL);
  printf("main(): Esperando %d segundos...\n", waittime);
  sleep(waittime);
  set_thread_flag(1);
  printf("main(): Esperando %d segundos...\n", waittime);
  sleep(waittime);
  return 0;
}