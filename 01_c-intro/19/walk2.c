#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stage.h"

void walk(MAZE* maze){
    int x=2, y=2, w=maze->width;
    char* m=maze->map;
    clock_t start=clock();

    for (int c; (c=getch())!='q';){
        add_char(x, y, m[x+w*y]);
        int ox=x, oy=y;

        x+=(c==KEY_RIGHT || c=='l')-(c==KEY_LEFT || c=='h');
        y+=(c==KEY_DOWN || c=='j')-(c==KEY_UP || c=='k');
        if (m[x+w*y]=='#') x=ox, y=oy;
        add_char(x, y, 'W');

        if (m[x+w*y]!='G'){
            double t=(double)(clock()-start)/CLOCKS_PER_SEC;

            char s[1000];
            sprintf(s, "Time:%.2f - [Q] to quit.", t);

            attrset(COLOR_PAIR(0));
            mvaddstr(getmaxy(stdscr)-1, 0, s);
        }
        refresh();
    }
}

int main(void){
    MAZE* maze=new_stage();
    walk(maze);
    delete_stage(maze);
}