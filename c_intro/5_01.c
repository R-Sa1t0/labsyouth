#include <stdio.h>

int main(){
    int x, y;
    double z;
    printf("x : %d\n", x);
    printf("y : %d\n", y);
    printf("z : %g\n", z);
printf("\n");
    int radius = 2;
    double pi = 3.14;
    printf("%g\n", radius*radius*pi);
printf("\n");
    int price_food=980, price_drink=430;
    double discount_rate=0.3;
    printf("%g\n", (price_food+price_drink)*(1-discount_rate));
printf("\n");
    {
        int x = 1;
        printf("x : %d\n", x);
    }
    {
        int x = 2;
        printf("x : %d\n", x);
    }
printf("\n");

}