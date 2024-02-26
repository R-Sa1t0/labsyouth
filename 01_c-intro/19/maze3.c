#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fill.h"
#include "dig.h"
#include "solve.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
    if (argc!=3) {
        printf("usage: %s width height\n", argv[0]);
        return 1;
    }

    MAZE* maze=new_maze(atoi(argv[1]), atoi(argv[2]));

    dig_maze(maze);
    print_maze(maze);

    solve_maze(maze);
    print_maze(maze);

    delete_maze(maze);
}