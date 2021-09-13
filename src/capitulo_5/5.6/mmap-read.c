#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_LENGTH 0x100 

int main(int argc, char * const argv[]){
    int fd;
    void * file_memory;
    int integer;

    /*Open the file */
    if (argv[1]!=NULL){
        printf("Usage: %s <file>\n", argv[1]);
        fd = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);
    }else{
        printf("Usage: /tmp/integer-file\n");
        fd = open("/tmp/integer-file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    }

    /*Create a memory mapping*/
    file_memory = mmap(0,FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd ,0);
    
    close(fd);

    /*Read the integer, print it out, and double it */
    sscanf(file_memory,"%d", &integer);
    printf("value: %d\n",integer);
    sprintf((char *) file_memory, "%d\n ",2*integer);

    /*Release the memory (unnecessary because the program exits)*/
    munmap(file_memory,FILE_LENGTH);

    return 0;
}