#include <stdio.h>

int main(){
    char c = 'c';
    short s = 41;
    int i = 42;
    int *i_ptr = &i;
    printf("c: %c\n", c);
    printf("s: %u\n", s);
    printf("i: %d\n", i);
    printf("memory space: %ld\n", i_ptr);
    printf("value of i_ptr space: %d\n", *i_ptr);
    printf("************************\n");
    *i_ptr = 133; //Dereferencing
    
    printf("value of i_ptr space: %d\n", *i_ptr);
    printf("i: %d\n", i);

    return 0;

}