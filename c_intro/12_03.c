#include <stdio.h>
#include <stdalign.h>

typedef struct
{
    char c;
    short s;
    int i;
}A;
typedef struct
{
    char c;
    int i;
    short s;
}B;
typedef struct
{
    char c;
    short s;
    alignas(8) int i;
}A_;
typedef struct
{
    char c;
    alignas(8) int i;
    short s;
}B_;


int main(){
    A a;
    printf("%lu\n", sizeof a);
    printf("%p\n", &a);
    printf("%p\n", &a.c);
    printf("%p\n", &a.s);
    printf("%p\n", &a.i);
    puts("");

    B b;
    printf("%lu\n", sizeof b);
    printf("%p\n", &b);
    printf("%p\n", &b.c);
    printf("%p\n", &b.i);
    printf("%p\n", &b.s);
    puts("");

    printf("%lu\n", alignof(char));
    printf("%lu\n", alignof(short));
    printf("%lu\n", alignof(int));
    printf("%lu\n", alignof(long));
    printf("%lu\n", alignof(char));
    printf("%lu\n", alignof(float));
    printf("%lu\n", alignof(double));
    puts("");

    printf("%lu\n", alignof(A));
    printf("%lu\n", alignof(B));
    puts("");

    printf("%lu\n", sizeof(A_));
    printf("%lu\n", alignof(A_));
    puts("");

    printf("%lu\n", sizeof(B_));
    printf("%lu\n", alignof(B_));



}