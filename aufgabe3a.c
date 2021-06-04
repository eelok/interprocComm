#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
    int id = fork();
    int counter = 0;
    int timer = 0;
    if(id == 0) {
        while (counter != 10){
           printf("child: id: %d\n", getpid()); 
           sleep(1);
           counter++;
        }
    } else {
        while(counter != 10){
            printf("parent: id: %d\n", getpid());
            while(timer <= 5){
                sleep(1);  
                timer++;         
            }
            kill(id, 15);
            counter++;
        }
    }
}