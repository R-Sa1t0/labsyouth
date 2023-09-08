#include <stdio.h>
#include <limits.h>

int main(){
    printf("%d\n", 3/2);
    //printf("%d\n", 3/0);
printf("\n");
    printf("%g\n", 3.0/2);
    printf("%g\n", 3.0/0);
printf("\n");
    printf("%08x\n", 0x1234<<0);
    printf("%08x\n", 0x1234<<16);
    printf("%08x\n", 0x1234<<20);
    printf("%08x\n", 0x1234<<24);
    printf("%08x\n", 0x1234<<28);
    printf("%08x\n", 0x1234<<32);
printf("\n");
    printf("%d\n", printf("a")+printf("b"));
printf("\n");  
    printf("%d%d\n", printf("Left"), printf("Right"));
printf("\n");
    printf("%d\n", CHAR_BIT);
printf("\n");
    printf("%4d\n", -100);
    printf("%4d\n", -100>>1);
    printf("%4d\n", -100>>2);
    printf("%4d\n", -100>>3);
    printf("%4d\n", -100>>4);
    printf("%4d\n", -100>>5);
    printf("%4d\n", -100>>6);
    printf("%4d\n", -100>>7);
    printf("%4d\n", -100>>8);
}