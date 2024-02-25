#include <stdio.h>

int main(){
    FILE* ifp=fopen("15_08.c","rb");
    FILE* ofp=fopen("15_08.out.c", "wb");

    char c[100];
    int n;
    while ((n=fread(c, 1, sizeof c, ifp))>0)
        fwrite(c,1,n,ofp);

    fclose(ifp);
    fclose(ofp);
}