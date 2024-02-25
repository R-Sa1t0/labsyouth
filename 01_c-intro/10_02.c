#include <stdio.h>

int caps(int c){
    if ('a'<=c && c<='z') return c-'a'+'A';
    return c;
}
int caps2(int c){
    return 'a'<=c && c<='z' ? c-'a'+'A' : c;
}

int main(){
    int c = getchar();

    putchar(caps(c));
    putchar('\n');

    putchar(caps2(c));
    putchar('\n');
}