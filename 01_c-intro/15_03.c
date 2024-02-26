#include <stdio.h>

int main(){
    FILE* fp=fopen("15_01.c", "r");
    char s[1000];
    for (int i=1; fgets(s, sizeof s, fp); i++)
        printf("%2d : %s", i, s);
    fclose(fp);
    puts("");
}