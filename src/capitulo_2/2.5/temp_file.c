/**
 * Listing 2.5 temp_file.c Using mkstemp
 * Francisco Alejandro Sanabria Zelaya
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef int temp_file_handle;

temp_file_handle write_temp_file (char * buffer, size_t length)
{
    char temp_filename[] = "/tmp/temp_file.XXXXXX";
    
    int fd = mkstemp(temp_filename);

    unlink(temp_filename);
    
    write (fd, &length, sizeof (length));
    write(fd, buffer,length);

    return fd;
}

char * read_temp_file (temp_file_handle temp_file, size_t * length){
    
    char * buffer;
    
    int fd = temp_file;

    lseek(fd,0,SEEK_SET);

    read(fd,length,sizeof(*length)); 

    buffer = (char *) malloc(*length);
    
    read(fd, buffer,*length);

    close(fd);

    return buffer;
}

int main(int argc, char * argv[]){

    char * buffer;
    size_t length;
    temp_file_handle temp_file;

    buffer = (char *) malloc(100);
    
    for(int i = 0; i <99; i++){
        buffer[i] = 'a';
    }
    buffer[100] = '\0';
    length = 100;
    temp_file = write_temp_file(buffer,length);
    buffer = read_temp_file(temp_file,&length);
    printf("%s\n",buffer);
    free(buffer);
    return EXIT_SUCCESS;
}