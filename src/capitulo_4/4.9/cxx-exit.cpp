#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

bool value = false;

extern void change_bool_value(){
    value = !value;
}

extern bool should_exit_thread_immediately (){
    return value;
};


class ThreadExitException
{
public:
    ThreadExitException(void * return_value)
        : thread_return_value_ (return_value)
    {   
    }

    void * DoTheadExit(){
        pthread_exit (thread_return_value_);
    }

private:
    void * thread_return_value_;
};

void do_some_work(){
    while(1){
        /* do here */
        printf("hello ");
        if (should_exit_thread_immediately()){
            throw ThreadExitException(NULL);
        }
    }
}

void * thread_function(void * arg){
    try{
        do_some_work();
    }catch(ThreadExitException e){
        e.DoTheadExit();
    }
    return NULL;
}

void * thread_sleep_function(void * arg){
    sleep(3);
    change_bool_value();
    printf("\nchange state value to true after 3 seconds\n");
    return NULL;
}

int main(){
    pthread_t thread;
    pthread_t time;

    pthread_create(&thread, NULL, &thread_function, NULL);
    pthread_create(&time, NULL, &thread_sleep_function, NULL);

    pthread_join(time, NULL);
    return 0;
}