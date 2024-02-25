#include <stdio.h>

int main(){
    FILE* fp=fopen("15_01.c", "r");
    char s[1000];
    fgets(s, sizeof s, fp);
    printf("%s", s);
    fclose(fp);
}