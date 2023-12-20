#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    printf("argc : %d\n", argc);
    for (int i=0; i<argc; i++) printf("argv[%d] : %s\n", i, argv[i]);

    if (argc<2){
        printf("usage: %s integer ...\n", argv[0]);
        return 1;
    }
    int total=0;
    for (int i=1; i<argc; i++) total+=atoi(argv[i]);
    printf("total : %d\n", total);
    printf("average : %g\n", (double)total/(argc-1));
}