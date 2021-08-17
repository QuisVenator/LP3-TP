#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int spawn(char * program, char ** arg_list){
    pid_t child_pid;
    child_pid = fork();
    if(child_pid != 0){
        return child_pid;
    }else{
        execvp(program, arg_list);
        printf(stderr, "an error ocurred in execvp\n");
        abort();
    }
}

int main(){
    char * arg_list[] = {
        "ls", //the first argument is the program name
        "-l",
        "/",
        NULL
    };

    spawn("ls", arg_list);

    printf("done with main program \n");
    return 0;
}