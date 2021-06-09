#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int parent_id;
    int firstChild_id, secondChild_id;
    int fd[2];
    parent_id = getpid();

    if(pipe(fd) != 0){
        printf("Error initialising pipe!\n");
        exit(1);
    }

    if ((firstChild_id = fork()) == 0) { //First Child Kain
        firstChild_id = getpid();
        char kill_instruction[] = "kill";
        char notKill[] = "not kill";
        for(int i = 0; i <= 6; i++){
            if(i == 6){
                write(fd[1], kill_instruction, strlen(kill_instruction));
            } else {
                write(fd[1], notKill, strlen(notKill));
                printf("Kain ID: %d, its Parent ID: %d\n", firstChild_id, parent_id);
            }
            close(fd[0]);
            sleep(1);
        }
    } else { //Parent Process
        if((secondChild_id = fork())== 0){ //Second Child Abel
            secondChild_id = getpid();
            close(fd[1]);
            while(1) {
                char buffer[200] = "";
                char killMessage[] = "kill";
                int read_byte = read(fd[0], buffer, 200);
                printf("Abel PID: %d, its parent: %d\n", secondChild_id, getppid());
                int res = strcmp(buffer, killMessage); 
                if(res == 0) {                    
                    printf(">>>>>>Kain killed Abel<<<<<<<<<\n");
                    kill(secondChild_id, 15);                  
                }
                sleep(1);
            }
        } else {//Parent Process
            for (int i = 0; i < 10; i++){
                printf("Parent ID %d\n", getpid());
                sleep(1);
            }
        }
    }
    return 0;
}