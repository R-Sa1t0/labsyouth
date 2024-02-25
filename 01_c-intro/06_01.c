#include <stdio.h>
#include <stdbool.h>

int main(){
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d==%d : %d\n", x, y, x==y);
        printf("%d!=%d : %d\n", x, y, x!=y);
        printf("%d<%d  : %d\n", x, y, x<y);
        printf("%d>%d  : %d\n", x, y, x>y);
        printf("%d<=%d : %d\n", x, y, x<=y);
        printf("%d>=%d : %d\n", x, y, x>=y);
    }
puts("");
    {
        float x;
        double y;
        scanf("%f%lf", &x, &y);
        printf("%g==%g : %d\n", x, y, x==y);
        printf("%g!=%g : %d\n", x, y, x!=y);
        printf("%g<%g  : %d\n", x, y, x<y);
        printf("%g>%g  : %d\n", x, y, x>y);
        printf("%g<=%g : %d\n", x, y, x<=y);
        printf("%g>=%g : %d\n", x, y, x>=y);
        printf("x : %.02f\n", x);
        printf("y : %.02f\n", y);
    }
puts("");
    {
        int hour;
        printf("hour : ");
        scanf("%d", &hour);
        printf("open   : %d\n", 8<=hour && hour<=22);
        printf("closed : %d\n", hour<8 || 22<hour);
        printf("open   : %d\n", !(hour<8 || 22<hour));
        printf("closed : %d\n", !(8<=hour && hour<=22));
    }
puts("");
    {
        int x;
        scanf("%d", &x);
        x==0 && puts("X==0");
        x==0 || puts("X!=0");
    }
puts("");
    {
        int x, y;
        scanf("%d%d", &x, &y);
        _Bool b=x==y;
        printf("x==y : %d\n", b);
    }
puts("");
    {
        bool x=true, y=false;
        printf("x : %d\n", x);
        printf("y : %d\n", y);
    }
}