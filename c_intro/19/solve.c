#include "solve.h"

static int solve(MAZE* maze, int p){
    int w=maze->width;
    char* m=maze->map;
    int u[]={1, -1, w, -w};

    for (int i=0; i<4; i++){
        int p1=p+u[i], p2=p1+u[i];
        if (m[p1]==' '){
            m[p1]='o';
            if (m[p2]=='G') return 1;
            m[p2]='o';
            if (solve(maze, p2)) return 1;
            m[p1]=m[p2]=' ';
        }
    }

    return 0;
}

void solve_maze(MAZE* maze){
    solve(maze, 2+maze->width*2);
}