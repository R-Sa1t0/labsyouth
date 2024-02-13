#include <stdio.h>

int add(int a, int b);

int main() {
    printf("%d\n", add(3, 4));
}

/*
clang -o bin/bin 16_02.c 16_02_def.c

or 

clang -c bin/16_02.c
clang -c bin/16_02_def.c
clang -o bin/out bin/16_02.o bin/16_02_def.o
*/ 
