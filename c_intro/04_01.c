#include <stdio.h>

int main(void){
    printf("3 + 2 = %d\n", 3+2);
    printf("3 - 2 = %d\n", 3-2);
    printf("3 * 2 = %d\n", 3*2);
    printf("3 / 2 = %d\n", 3/2);
    printf("3 %% 2 = %d\n", 3%2);
puts("");
    printf(" 3 / 2 = %2d\n", 3/2);
    printf(" 3 /-2 = %2d\n", 3/-2);
    printf("-3 / 2 = %2d\n", -3/2);
    printf("-3 /-2 = %2d\n", -3/-2);
puts("");
    printf(" 3 %% 2 = %2d\n", 3%2);
    printf(" 3 %%-2 = %2d\n", 3%-2);
    printf("-3 %% 2 = %2d\n", -3%2);
    printf("-3 %%-2 = %2d\n", -3%-2);
puts("");
    printf("1.2 + 3.4 = %g\n", 1.2 + 3.4);
    printf("1.2 - 3.4 = %g\n", 1.2 - 3.4);
    printf("1.2 * 3.4 = %g\n", 1.2 * 3.4);
    printf("1.2 / 3.4 = %g\n", 1.2 / 3.4);
puts("");
    printf("2 + 3 * 4 = %d\n", 2+3*4);
    printf("(2+3) * 4 = %d\n", (2+3)*4);
    printf("2 - 3 + 4 = %d\n", 2-3+4);
puts("");
    printf("88 * 0.9 = %g\n", 88*0.9);
    printf("(int)(88 * 0.9) = %d\n", (int)(88*0.9));
puts("");
    printf("(85+90+95+100)/4 = %d\n", (85+90+95+100)/4 );
    printf("(85+90+95+100)/4.0 = %g\n", (85+90+95+100)/4.0 );
    printf("(85+90+95+100)/4 = %g\n", (double)(85+90+95+100)/4 );
}