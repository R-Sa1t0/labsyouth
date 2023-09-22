#include <stdio.h>

#define PI 3.14

int main(){
    {
        const double pi = 3.14;
        double radius;
        printf("radius: ");
        scanf("%lf", &radius);
        printf("volume: %.2lf\n", 4.0/3.0*pi*radius*radius*radius);
        printf("volume: %.2lf\n", 4.0/3.0*PI*radius*radius*radius);
    }
puts("");
    {
        enum{RED, GREEN, BLUE};
        printf("%d\n", RED);
        printf("%d\n", GREEN);
        printf("%d\n", BLUE);
    }
puts("");
    {
        enum{RED=20, GREEN=30, BLUE=40};
        printf("%d\n", RED);
        printf("%d\n", GREEN);
        printf("%d\n", BLUE);
    }
puts("");
    {
        enum{SEP=9, OCT, NOV, DEC, JAN=1, FEB, MAR, APR};
        printf("%d\n", SEP);
        printf("%d\n", OCT);
        printf("%d\n", NOV);
        printf("%d\n", DEC);
        printf("%d\n", JAN);
        printf("%d\n", FEB);
        printf("%d\n", MAR);
        printf("%d\n", APR);
    }
puts("");
    {
        enum DAY {MON, TUE, WED, THU, FRI, SAT, SUN} day=TUE;
        printf("%d\n", day);
        printf("%d\n", FRI-day);
    }
}