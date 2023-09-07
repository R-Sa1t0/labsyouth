#include <stdio.h>

int main(void){
    printf("Hello. %dyen\n", 100);
    printf("%d , %d \n", 200, 200);

    printf("%x\n", 0xabcdef);
    printf("%X\n", 0xabcdef);
    printf("%d\n", 0xabcded);

    printf("%o \n", 0755);
    printf("%X \n", 0755);
    printf("%d \n", 0755);

    printf("pi = %f \n", 3.1415);
    printf("pi = %.2f \n", 3.1415);
    printf("%.20f \n", 0.1);
    printf("%.20f \n", 0.5);
    printf("%.20f \n", 0.25);
    printf("%.20f \n", 0.125);
    printf("%.20f \n", 0.0525);
    printf("%f \n", 6.02e23);
    printf("%.36f \n", 6.63e-24);
    printf("%e \n", 6.02e23);
    printf("%E \n", 6.63e-24);
    printf("%.02e \n", 6.02e23);
    printf("%.02E \n", 6.63e-24);
    printf("%g \n", 6.02e23);
    printf("%G \n", 6.63e-24);

    printf("name number density");
    printf("%s %d %.2f\n", "gold", 79, 19.32);
    printf("%s %d %.2f\n", "silver", 47, 10.49);
    printf("%s %d %.2f\n", "copper", 29, 8.94);
    printf("%s %d %.2f\n", "iron", 26, 7.87);

    printf("%-6s %6s %7s\n", "name", "number", "density");
    printf("%-6s %6d %7.2f\n", "gold", 79, 19.32);
    printf("%-6s %6d %7.2f\n", "silver", 47, 10.49);
    printf("%-6s %6d %7.2f\n", "copper", 29, 8.94);
    printf("%-6s %6d %7.2f\n", "iron", 26, 7.87);
    return 0;
}