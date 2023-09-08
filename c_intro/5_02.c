#include <stdio.h>

int main(){
    int x1 = 123;
    printf("x1 : %d\n", x1);
    {
        int x1 = 456;
        printf("x1 : %d\n", x1);
    }
    printf("x1 : %d\n", x1);
printf("\n");
    printf("%lu\n", sizeof(short));
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(long));
    printf("%lu\n", sizeof(long long));
printf("\n");
    {
        short x = 10000;
        int y = 100000000;
        long long z = 1000000000000;
        printf("%d\n", x);
        printf("%d\n", y);
        printf("%lld\n", z);
printf("\n");
    printf("%d\n", x+y);
    printf("%lld\n", y+z);
    printf("%lld\n", z+x);
    }
printf("\n");
    printf("%lld\n", sizeof(float));
    printf("%lld\n", sizeof(double));
    printf("%lld\n", sizeof(long double));
printf("\n");
    {
        float x = 1/3.0;
        double y = 1/3.0;
        long double z = 1/3.0L;
        printf("%.40f\n", x);
        printf("%.40f\n", y);
        printf("%.40Lf\n", z);
    }
}