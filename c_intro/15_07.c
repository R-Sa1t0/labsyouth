#include <stdio.h>

int main(){
    FILE* ifp=fopen("15_06.c", "r");
    FILE* ofp=fopen("15_07.out.c", "w");

    for (int c; (c=fgetc(ifp))!=EOF; fputc(c, ofp));
    fclose(ifp);
    fclose(ofp);
}