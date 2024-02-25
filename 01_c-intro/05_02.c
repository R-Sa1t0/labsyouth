#include <stdio.h>

int main(){
    int x1 = 123;
    printf("x1 : %d\n", x1);
    {
        int x1 = 456;
        printf("x1 : %d\n", x1);
    }
    printf("x1 : %d\n", x1);
puts("");
    printf("%lu\n", sizeof(short));
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(long));
    printf("%lu\n", sizeof(long long));
puts("");
    {
        short x = 10000;
        int y = 100000000;
        long long z = 1000000000000;
        printf("%d\n", x);
        printf("%d\n", y);
        printf("%lld\n", z);
puts("");
    printf("%d\n", x+y);
    printf("%lld\n", y+z);
    printf("%lld\n", z+x);
    }
puts("");
    printf("%lld\n", sizeof(float));
    printf("%lld\n", sizeof(double));
    printf("%lld\n", sizeof(long double));
puts("");
    {
        float x = 1/3.0;
        double y = 1/3.0;
        long double z = 1/3.0L;
        printf("%.40f\n", x);
        printf("%.40f\n", y);
        printf("%.40Lf\n", z);
    }
puts("");
    {
        int doller = 100, rate = 105;
        printf("%d\n", doller * rate);
        rate=115;
        printf("%d\n", doller * rate);
    }
puts("");
    {
        int x = 1/2.0;
        printf("%d\n", x);
        x = 3/2.0;
        printf("%d\n", x);
    }
puts("");
    {
        double component = 1;
        component*=1.4;
        printf("%g\n", component);
        component*=1.4;
        printf("%g\n", component);
        component*=1.4;
        printf("%g\n", component);
        component*=1.4;
        printf("%g\n", component);
        component*=1.4;
        printf("%g\n", component);
        component*=1.4;
        printf("%g\n", component);
        component*=1.4;
        printf("%g\n", component);
        component*=1.4;
        printf("%g\n", component);
    }
puts("");
    {
        int x;
        printf("%d\n", x=123);
        printf("%d\n", x);
    }
}