#include <stdio.h>

static void f(void){
    puts("Hello from sub-f");
}

void g(void){
    f();
}