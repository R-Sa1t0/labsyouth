#include <stdio.h>

int main(int argc, char* argv[]){
    if (argc!=2){
        printf("usage : %s file\n", argv[0]);
        return 1;
    }

    FILE* fp=fopen(argv[1], "r");
    if (!fp) {
        printf("Can't open %s\n", argv[1]);
        return 1;
    }

    char s[1000];
    for (int i=1; fgets(s, sizeof s, fp); i++)
        printf("%2d : %s", i, s);
    
    fclose(fp);
}