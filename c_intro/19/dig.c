#include <stdlib.h>
#include "dig.h"

void dig_maze(MAZE* maze){
    int w=maze->width, h=maze->height;
    char* m=maze->map;
    int u[]={1, -1, w, -w};

    m[2+2*w]=' ';
    for (int n=1; n<(w-4)/2*(h-3)/2;){
        for (int y=2; y<h-2; y+=2){
            for (int x=2; x<w-3; x+=2){
                int p=x+y*w;
                if (m[p]=='#') continue;
                for (int v; v=u[rand()%4], m[p+v*2]=='#'; n++){
                    m[p+v]=m[p+v*2]=' ';
                    p+=v*2;
                }
            }
        }
    }

    m[2+2*w]='S';
    m[(w-4)+(h-3)*w]='G';
}