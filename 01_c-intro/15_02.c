#include <stdio.h>

int main(){
    FILE* fp=fopen("15_01.c", "r");
    char s[1000];
    while (fgets(s, sizeof s, fp)!=NULL) printf("%s", s);
    fclose(fp);
    puts("");
}