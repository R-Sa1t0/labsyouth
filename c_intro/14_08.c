#include <stdio.h>

int add(int x, int y){ return x+y; }
int sub(int x, int y){ return x-y; }
int mul(int x, int y){ return x*y; }
int div(int x, int y){ return x/y; }
int mod(int x, int y){ return x%y; }

int main(){
    int (*p1)(int,int)=add;
    printf("%d\n", p1(1,2));
    puts("");

    int (*p[])(int, int)={add, sub, mul, div, mod};
    int n=sizeof p/sizeof p[0];
    for (int i=0; i<n; i++) printf("%d\n", p[i](12,3));
}