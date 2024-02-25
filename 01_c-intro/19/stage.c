#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dig.h"
#include "stage.h"

void add_char(int x, int y, int c){
    attrset(COLOR_PAIR(c%COLOR_PAIRS));
    mvaddch(y, x, c);
}
MAZE* new_stage(){
    if (!initscr()) {
        puts("initscr failed.");
        exit(1);
    }

    keypad(stdscr, TRUE);
    timeout(0);
    curs_set(0);
    noecho();
    start_color();

    for (int i=0; i<COLOR_PAIRS; i++){
        init_pair(i, COLOR_WHITE, COLOR_BLACK);
    }
    init_pair('+', COLOR_CYAN, COLOR_BLUE);
    init_pair('#', COLOR_MAGENTA, COLOR_RED);
    init_pair('S', COLOR_GREEN, COLOR_BLACK);
    init_pair('G', COLOR_GREEN, COLOR_BLACK);
    init_pair('W', COLOR_YELLOW, COLOR_BLACK);

    srand(time(NULL));
    MAZE* maze=new_maze(getmaxx(stdscr), getmaxy(stdscr)-1);
    dig_maze(maze);

    erase();
    char* m=maze->map;
    for (int y=0, p=0; m[p]; y++, p++){
        for (int x=0; m[p]!='\n'; x++, p++) add_char(x, y, m[p]);
    }
    refresh();

    return maze;
}
void delete_stage(MAZE* maze){
    delete_maze(maze);
    endwin();
}