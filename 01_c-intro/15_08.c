#include <stdio.h>

int main(){
    FILE* fp=fopen("15_07.c", "rb");
    for (int i=1, c; (c=getc(fp))!=EOF; i++){
        printf("%02x%c", c, i%16?' ':'\n');
    }
    puts("");
    fclose(fp);
}