#include <stdio.h>

int main(){
    char buffer[3] = {41, 42, 43};
    char* b_start = buffer;
    printf("result: %d\n", buffer[0]);
    printf("result: %d\n", b_start[0]);
    printf("result: %d\n", b_start[2]);
    printf("result: %d\n", b_start[4]);
}