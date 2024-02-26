#include <stdio.h>

int main(){
    FILE* fp=fopen("15_06.c","r");
    //for (int c; (c=fgetc(fp))!=EOF; putchar(c));
    for (int c; c=fgetc(fp),c!=EOF; putchar(c));
    puts("");
    
    fclose(fp);
}