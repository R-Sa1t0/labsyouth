#include <stdio.h>

int main(){
    {
        puts("char code");
        printf("%4c %4d\n", '0', '0');
        printf("%4c %4d\n", '1', '1');
        printf("%4c %4d\n", '2', '2');

        puts("char code");
        printf("%4c %4d\n", 'A', 'A');
        printf("%4c %4d\n", 'B', 'B');
        printf("%4c %4d\n", 'C', 'C');

        puts("char code");
        printf("%4c %4d\n", 'a', 'a');
        printf("%4c %4d\n", 'b', 'b');
        printf("%4c %4d\n", 'c', 'c');        
    }
    {
        char c=0xff;
        printf("%d\n", c);

        signed char sc=0xff;
        printf("%d\n", sc);

        unsigned char uc=0xff;
        printf("%d\n", uc);
    }
    {
        //char c;
        //scanf("%c", &c);
        //printf("%d\n", c);
    }
    {
        int c = getchar();
        if('a'<=c && c<='z'){
            putchar(c-'a'+'A');
            putchar('\n');
        }
    }
}