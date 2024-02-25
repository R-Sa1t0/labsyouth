#include <stdio.h>

int main(int argc, char* argv[]){
    int x=123;
    printf("x  : %d\n", x);
    int* p=&x;
    printf("p  : %p\n", p);
    printf("*p : %d\n", *p);
    int** q=&p;
    printf("q  : %p\n", p);
    printf("*q : %p\n", *q);
    printf("**q: %d\n", **q);

    for (char** p=argv; *p; p++){
        for (char* q=*p; *q; q++) printf("%c ", *q);
        puts("");
    }
}