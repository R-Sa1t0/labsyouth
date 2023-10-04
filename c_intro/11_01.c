#include <stdio.h>
#include <stdarg.h>


int factorial(int n){
    if (n>1) return n*factorial(n-1);
    return 1;
}

int factorial2(int n){
    return n>1 ? n*factorial2(n-1) : 1;
}

int gcd(int x, int y){
    if (!y) return x;
    if (x%y) return gcd(y, x%y);
    return y;
}
int gcd2(int x, int y){
    return !y ? x : x%y ? gcd2(y, x%y) : y;
}

int sum(int count, ...){
    va_list list;
    va_start(list, count);

    int total = 0;
    for (int i=0; i<count; i++) total=va_arg(list, int);
    va_end(list);

    return total;
}


int main(){
    printf("%d\n", factorial(3));
    printf("%d\n", factorial(6));
    printf("%d\n", factorial(12));

    puts("");

    printf("%d\n", factorial2(3));
    printf("%d\n", factorial2(6));
    printf("%d\n", factorial2(12));

    puts("");

    printf("%d\n", gcd(36, 28));
    printf("%d\n", gcd(12345, 68790));
    printf("%d\n", gcd(12345, 0));

    puts("");

    printf("%d\n", gcd2(36, 28));
    printf("%d\n", gcd2(12345, 68790));
    printf("%d\n", gcd2(12345, 0));

    puts("");
    
    printf("%d\n", sum(2,3,4));
    printf("%d\n", sum(3,123,456,789));
}