#include <stdio.h>
#include <stdlib.h>
#include "fill.h"

static inline int max (int x, int y){return x>y?x:y;}
 
MAZE* new_maze(int width, int height){
    int w=(max(width, 9)-3)/2*2+4, h=(max(height, 7)-3)/2*2+3;
    char* m=malloc(w*h+1);
    
    m[w*h]='\0';
    for (int p=0; p<w*h; p++) m[p]='#';
    for (int y=0; y<h; y++) m[w-1+w*y]='\n';

    for (int x=0; x<w-1; x++) m[x]=m[x+w*(h-1)]='+';
    for (int y=0; y<h-1; y++) m[w*y]=m[w-2+w*y]='+';

    MAZE* maze=malloc(sizeof(MAZE));
    *maze=(MAZE){w, h, m};
    return maze;
}
void delete_maze(MAZE* maze){
    free(maze->map);
    free(maze);
}
void print_maze(MAZE* maze){
    puts(maze->map);
}