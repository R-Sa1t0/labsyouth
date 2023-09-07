#include <stdio.h>

int main(void){
    printf("%x\n", 0);
    printf("%x\n", ~0);
printf("\n");
    printf("%x\n", 0x0f0f00ff);
    printf("%x\n", ~0x0f0f00ff);
printf("\n");
    printf("%x\n", 0x1234567);
    printf("%x\n", ~0x1234567);
printf("\n");
    printf("%08x\n", 0x01234567&0x000fff000);
printf("\n");
    printf("%d\n", 4&3);
    printf("%d\n", 5&3);
    printf("%d\n", 6&3);
    printf("%d\n", 7&3);
printf("\n");
    printf("%d\n", 10&7);
    printf("%d\n", 20&7);
    printf("%d\n", 30&7);
    printf("%d\n", 40&7);
printf("\n");
    printf("%08x\n", 0x01234567|0x00f000f0);
    printf("%08x\n", 0x01234567|0x80000000);
printf("\n");
    printf("%08x\n", 0x01234567^0x0f0f0f0f);
    printf("%08x\n", 0x0e2c4a68^0x0f0f0f0f);
printf("\n");
    printf("%08x\n", 0x1234<<0);
    printf("%08x\n", 0x1234<<4);
    printf("%08x\n", 0x1234<<8);
    printf("%08x\n", 0x1234<<12);
    printf("%08x\n", 0x1234<<16);
    printf("%08x\n", 0x1234<<20);
    printf("%08x\n", 0x1234<<24);
    printf("%08x\n", 0x1234<<28);
printf("\n");
    printf("%4d\n", 100);
    printf("%4d\n", 100<<1);
    printf("%4d\n", (100<<1)+100);
    printf("%4d\n", 100<<2);
    printf("%4d\n", (100<<2)+100);
    printf("%4d\n", 100<<3);
    printf("%4d\n", (100<<3)+100);
    printf("%4d\n", (100<<3)+(100<<1));
printf("\n");
    printf("%08x\n", 0x1234>>0);
    printf("%08x\n", 0x1234>>4);
    printf("%08x\n", 0x1234>>8);
    printf("%08x\n", 0x1234>>12);
    printf("%08x\n", 0x1234>>16);
printf("\n");
    printf("%4d\n", 100);
    printf("%4d\n", 100>>1);
    printf("%4d\n", 100>>2);
    printf("%4d\n", 100>>3);
    printf("%4d\n", 100>>4);
    printf("%4d\n", 100>>5);
    printf("%4d\n", 100>>6);
    printf("%4d\n", 100>>7);
    printf("%4d\n", 100>>8);


    return 0;
}