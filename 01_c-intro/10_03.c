#include <stdio.h>

void f(int d){
    int e = d+4;
    printf("%d\n", e);
}

void g(int b){
    int c = b+2;
    f(c+3);
}

int main(){
    int a=0;
    g(a+1);
}