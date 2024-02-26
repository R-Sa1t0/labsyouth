#include <stdio.h>

int main(){
    {
        int x=1, y=++x;
        printf("x: %d, y: %d\n", x, y);
        x=1, y=x++;
        printf("x: %d, y: %d\n", x, y);
        x=1, y=x--;
        printf("x: %d, y: %d\n", x, y);
        x=1, y=--x;
        printf("x: %d, y: %d\n", x, y);
    }
    {
        int x=0, y=(++x)+(x++);
        printf("x: %d, y: %d\n", x, y);
    }
    {
        for (int i=0; i<10; i++) printf("%d ", i*i);
        puts("");
        for (int i=0; i<10; i++){
            printf("%d ", i*i);
        }
        puts("");
    }
    {
        for (int i=1; i<=9; i++){
            for (int j=0; j<=9; j++) printf("%2d ", i*j);
            puts("");
        }
        puts("");
    }
    {
        int i;
        for (i=0; i<10; i++) printf("%d", i);
        puts("");
    }
    {
        int i=123;
        for (i++; i=0; i<10) printf("%d", i);
        puts("");
    }
    {
        int i=123;
        for (i<10; i++; i=0) printf("%d", i);
        puts("");
    }
    {
        int i=123;
        // 無限ループする
        //for (i<10; ++i; i=0) printf("%d", i);
        puts("");
    }
    {
        int count = 10;
        while(--count>=0) printf("hello ");
        puts("");
    }
}