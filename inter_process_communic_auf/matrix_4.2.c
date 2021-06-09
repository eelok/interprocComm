#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>

const int NUMBER_OF_CLIENTS = 5;
const int pipe_fds[NUMBER_OF_CLIENTS][2];
const float vector[] = {0.8, 0, 0, 0, 0.25};
const float matrix[NUMBER_OF_CLIENTS][NUMBER_OF_CLIENTS] = {
        {0, 1, 2, 3, 4}, //0
        {1, 0, 1, 2, 3}, //1
        {2, 1, 0, 1, 2}, //2
        {3, 2, 1, 0, 1}, //3
        {4, 3, 2, 1, 0}  //4
};

float calculate(float num[], float vector[], int NUMBER_OF_CLIENTS) {
    float res = 0;
    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        res += (num[i] * vector[i]);
    }
    return res;
}

void openPipeForEachClient() {
    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        if (pipe(pipe_fds[i]) != 0) {
            printf("Error initialising pipe!\n");
        }
    }
}

void closePipeForEachClient() {
    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        for (int j = 0; j < 2; j++) {
            close(pipe_fds[i][j]);
        }
    }
}

int main() {
    openPipeForEachClient();

    int listOfClients[NUMBER_OF_CLIENTS] = {0, 0, 0, 0, 0};

    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        if ((listOfClients[i] = fork()) == 0) { // Client
            float result = calculate(matrix[i], vector, NUMBER_OF_CLIENTS);
            write(pipe_fds[i][1], &result, sizeof(result));
            printf("from CLIENT N:%d result %f\n", i + 1, result);
            return 0;
        }
    }
    sleep(1);
    for (int i = 0; i < NUMBER_OF_CLIENTS; i++){ // server
        float buffer[200];
        float read_byte = read(pipe_fds[i][0], &buffer, sizeof(buffer));
        printf("from SERVER: from client N:%d received: %f\n",i+1, *buffer);
    }
    closePipeForEachClient();
    exit(0);
}




