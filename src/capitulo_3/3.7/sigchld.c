#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

sig_atomic_t child_exit_status = 0;

void clean_up_child_process (int signal_number)
{
    /* Clean up the child process. */
    int status;
    wait (&status);
    /* Store its exit status in a global variable. */
    child_exit_status = status;
}
    
int main ()
{
    srand(time(NULL));
    /* Handle SIGCHLD by calling clean_up_child_process. */
    struct sigaction sigchld_action;
    memset (&sigchld_action, 0, sizeof (sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction (SIGCHLD, &sigchld_action, NULL);

    /* Now do things, including forking a child process. */
    /* Creamos un child que sale con codigo aleatorio*/
    pid_t child_pid;
    child_pid = fork () ;
    if(child_pid != 0) {
        printf("Esperamos hasta 5 segundos para tener alta probabilidad de que termina el proceso hijo\n");
    } else {
        exit(rand()%10); //salir con codigo aleatorio para demostrar funcionamiento
    }

    sleep(5);
    printf("Proceso hijo termino con exit = %d\n", WEXITSTATUS(child_exit_status));

    return 0;
}