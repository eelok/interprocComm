#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
// #define int LINE_0[5] = {0, 1, 2, 3, 4} //1
// #define int LINE_1[5] = {1, 0, 1, 2, 3} //2
// #define int LINE_2[5] = {2, 1, 0, 1, 2}
// #define int LINE_3[5] = {3, 2, 1, 0, 1}
// #define int LINE_4[5] = {4, 3, 2, 1, 0}
// #define int COLUMMN[5] = {4/5, 0, 0, 0, 1/4}

//todo наверное нужно делать арруй с длиной
float calculate(float num1[], float num2[]){
    float res = 0;
    for(int i = 0; i < 5; i++){
        res += (num1[i] * num2[i]);
    }

    return res;
}

int main(){
    int fd[2];
    int client_001, client_002, client_003, client_004, client_005;
 
    if(pipe(fd)!= 0){
        printf("Error initialisieren pipe\n");
        exit(1);
    }

    if((client_001 = fork()) == 0) { //First client
            float row001[] = {0, 1, 2, 3, 4};
            float column[] = {0.8, 0, 0, 0, 0.25};
            float res = calculate(row001, column);
            printf("First Client: %f\n", res);
            write(fd[1], &res, sizeof(res));
            close(fd[0]);
            sleep(1);   
    } else {
        if((client_002 = fork()) == 0){ //Second client
            float row002[] = {1, 0, 1, 2, 3};
            float column[] = {0.8, 0, 0, 0, 0.25};
            float res = calculate(row002, column);
            printf("Second Client: %f\n", res);
            write(fd[1], &res, sizeof(res));
            close(fd[0]);
            sleep(1);
        } else{ 
            if((client_003 = fork()) == 0){ //Third Client
                float row003[] = {2, 1, 0, 1, 2};
                float column[] = {0.8, 0, 0, 0, 0.25};
                float res = calculate(row003, column);
                printf("Third Client: %f\n", res);
                write(fd[1], &res, sizeof(res));
                close(fd[0]);
                sleep(1);
            } else {
                if((client_004 = fork()) == 0){  //Fourth Сlient
                    float row004[] = {3, 2, 1, 0, 1};
                    float column[] ={0.8, 0, 0, 0, 0.25};
                    float res = calculate(row004, column);
                    printf("Fourth Client: %f\n", res);
                    write(fd[1], &res, sizeof(res));
                    close(fd[0]);
                    sleep(1);
                } else {
                    if((client_005 = fork()) == 0){ //Fifth client
                        float row005[] = {4, 3, 2, 1, 0};
                        float column[] ={0.8, 0, 0, 0, 0.25};
                        float res = calculate(row005, column);
                        printf("Fifth Client: %f\n", res);
                        write(fd[1], &res, sizeof(res));
                        close(fd[0]);
                        sleep(1);
                    } else {
                        // wait(NULL);
                        float buffer[255];
                        while (1){
                            int read_byte = read(fd[0], buffer, sizeof(buffer));
                            if(read_byte == 0){
                                break;
                            }
                            printf("from parent: %f\n", *buffer);
                            sleep(1);
                        }
                    }
                    
                }
            }  
        }
    }
    exit(0);
}


// int main() {
//     float row002[] = {1, 0, 1, 2, 3};
//     float column[] = {0.8, 0, 0, 0, 0.25};
//     float res2 = calculate(row002, column);
//     printf("res2=%f\n", res2);
// }

