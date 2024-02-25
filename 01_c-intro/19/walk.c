#include <curses.h>
#include "stage.h"

int main(void){
    MAZE* maze=new_stage();
    while (getch()!='q');
    delete_stage(maze);
}