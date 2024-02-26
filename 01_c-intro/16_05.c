#include <stdio.h>

extern int major, minor;

int main(){
    printf("%d.%d\n", major, minor);
}