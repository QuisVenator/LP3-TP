#include <stdio.h>
#include <unistd.h>//PROGRAMA SOLO EJECUTABLE EN SO BASADOS EN GNU/LINUX
#include <pthread.h>

#define waittime 2

void do_work (){
    printf("do_work (): Haciendo el trabajo...\n");
}

int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;

void initialize_flag ()
{
  /* Initialize the mutex and condition variable.  */
  pthread_mutex_init (&thread_flag_mutex, NULL);
  pthread_cond_init (&thread_flag_cv, NULL);
  /* Initialize the flag value.  */
  
  thread_flag = 0;
  printf("initialize_flag(): Bandera inicalizada y seteada a: %d\n",thread_flag);
}

/* Calls do_work repeatedly while the thread flag is set; blocks if
   the flag is clear.  */

void* thread_function (void* thread_arg)
{
  /* Loop infinitely.  */
  while (1) {
    /* Lock the mutex before accessing the flag value.  */
    pthread_mutex_lock (&thread_flag_mutex);
    while (!thread_flag){
      /* The flag is clear.  Wait for a signal on the condition
	 variable, indicating the flag value has changed.  When the
	 signal arrives and this thread unblocks, loop and check the
	 flag again.  */
   printf("thread_function(): Esperando cambio de valor en la bandera: %d\n",thread_flag);
      pthread_cond_wait (&thread_flag_cv, &thread_flag_mutex);
    printf("thread_function(): Bandera cambio a: %d\n",thread_flag);
  
    /* When we've gotten here, we know the flag must be set.  Unlock
       the mutex.  */
    pthread_mutex_unlock (&thread_flag_mutex);
    /* Do some work.  */
    do_work();
    }
  }
  return NULL;
}

/* Sets the value of the thread flag to FLAG_VALUE.  */

void set_thread_flag (int flag_value)
{
  /* Lock the mutex before accessing the flag value.  */
  pthread_mutex_lock (&thread_flag_mutex);
  /* Set the flag value, and then signal in case thread_function is
     blocked, waiting for the flag to become set.  However,
     thread_function can't actually check the flag until the mutex is
     unlocked.  */
     printf("set_thread_flag(): Bandera seteada a: %d\n",flag_value);
  thread_flag = flag_value;
  pthread_cond_signal (&thread_flag_cv);
  /* Unlock the mutex.  */
  pthread_mutex_unlock (&thread_flag_mutex);
}

pthread_t thread_id;

int main(){
    initialize_flag();       
    pthread_create(&thread_id,NULL,thread_function,NULL);
    printf("main(): Esperando %d segundos...\n",waittime);
    sleep(2); 
    set_thread_flag (1);
    printf("main(): Esperando %d segundos...\n",waittime);
    sleep(2);    
    return 0;
}