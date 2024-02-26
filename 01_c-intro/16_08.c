#include <stdio.h>

int a=1;
extern int b;
static int c=3;

void h(int d){
    int e=5;
    extern int f;
    static int g=7;
    printf("%d %d %d %d %d %d %d\n", a, b, c, d, e, f, g);
}

int main(void){
    h(4);
}