#include <stdio.h>

static void f(void){
    puts("Hello from f");
}

void g(void);

int main(void){
    f();
    g();
    return 0;
}