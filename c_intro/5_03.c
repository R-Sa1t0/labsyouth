#include <stdio.h>

int main(){
    {
        int x;
        scanf("%d", &x);
        printf("%d\n", x*x);
    }
puts("");
    {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d+%d=%d\n", x, y, x+y);
        printf("%d-%d=%d\n", x, y, x-y);
        printf("%d*%d=%d\n", x, y, x*y);
        printf("%d/%d=%d\n", x, y, x/y);
        printf("%d%%%d=%d\n", x, y, x%y);
    }
puts("");
    {
        double inch;
        scanf("%lf", &inch);
        printf("%.03lf inch is %.03lf cm\n", inch, inch*2.54);
    }
}