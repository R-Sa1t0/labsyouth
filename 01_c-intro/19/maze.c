#include <stdio.h>
#include <stdlib.h>
#include "fill.h"

int main(int argc, char* argv[]){
    if (argc!=3){
        printf("usage: %s width height\n", argv[0]);
        return 1;
    }
    MAZE* maze=new_maze(atoi(argv[1]), atoi(argv[2]));
    print_maze(maze);
    delete_maze(maze);
}