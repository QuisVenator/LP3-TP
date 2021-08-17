struct job {
    /* Link field for linked list. */
    struct job* next;

    /* Para demostrar funcionamiento cada job debe encontrar la cantidad de
    divisores de un enter aleatiorio e imprimir */
    int num, cant_div;
};

void process_job(struct job* job);
void initialize_job_queue ();
void* thread_function (void* arg);
void enqueue_job ();
