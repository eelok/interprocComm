#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int fd[2];
    int first_child, second_child;

    if(pipe(fd) != 0){
        printf("Error by inintialising pipe\n");
        exit(1);
    }
    if( (first_child = fork()) == 0){ //first child
        char *hello = "hello";
        write(fd[1], hello, strlen(hello));
        close(fd[0]);
    } else { //parent
        if((second_child = fork()) == 0){ //second child
            char *world = "World!";
            write(fd[1], world, strlen(world));
            close(fd[0]);
        } else{
            close(fd[1]);
            char buffer[101];
            while (1){
                int read_byte = read(fd[0], buffer, 100);
                if(read_byte == 0){
                    break;
                }
                // fputs(buffer, stdout); 
                write(1, buffer, read_byte);
            }
        }   
    }
    exit(0);
}