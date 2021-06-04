#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int parent;
    int firstChild_id, secondChild_id;
    int fd[2];

    if(pipe(fd) != 0){
        printf("Error initialising pipe\n");
        exit(1);
    }

    if( (firstChild_id = fork()) == 0){//first child => Kain
        firstChild_id = getpid();
        char *message = "message from first child (Kain)";
        // printf("From First child; ID: %d, Parent ID: %d\n", firstChild_id, getppid());
        write(fd[1], message, strlen(message));
        close(fd[0]);
        sleep(1);

    } else { //parent 
        if((secondChild_id = fork()) == 0){ //second => Child Abel
            secondChild_id = getpid();
            // printf("From Second child; ID: %d, Parent ID: %d\n", secondChild_id, getppid());
            char buffer[201];
            int read_byte = read(fd[0], buffer, 200);
            printf("Abel: %s\n", buffer);
            sleep(1);
        } else{ //parent
            printf("From Parent; ID: %d\n", getpid());
            sleep(1);
        }
    }
    exit(0);
}