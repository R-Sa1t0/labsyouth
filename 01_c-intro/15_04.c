#include <stdio.h>

int main(){
    FILE* fp_src=fopen("15_01.c", "r");
    FILE* fp_dst=fopen("15_01.out", "w");

    char s[1000];
    while (fgets(s, sizeof s, fp_src))
        fputs(s, fp_dst);
    
    fclose(fp_src);
    fclose(fp_dst);
}