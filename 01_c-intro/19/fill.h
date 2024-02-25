#pragma once

typedef struct {
    int width, height;
    char* map;
} MAZE;

MAZE* new_maze(int width, int height);
void delete_maze(MAZE* maze);
void print_maze(MAZE* maze);
