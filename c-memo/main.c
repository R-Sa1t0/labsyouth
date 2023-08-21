#include <stdint.h>
#include <stdio.h>

struct A {
    int x;
};

struct B {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
};

struct C
{
    uint8_t n;
};

struct D
{
    char m;
};


int main()
{
    char buf[16];
    struct A *pa = (struct A*)buf;
    struct B *pb = (struct B*)buf;
    pa->x = 0x12345678;
    printf("pb : %02x %02x %02x %02x\n", pb->a, pb->b, pb->c, pb->d);

    char buf2[16];
    struct C *pc = (struct C*)buf2;
    struct D *pd = (struct D*)buf2;
    pc->n = 10;
    printf("pd : %02x\n", pd->m);
    return 0;
}