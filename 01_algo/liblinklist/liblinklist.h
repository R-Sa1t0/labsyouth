#ifndef LIBLINKLIST_H
#define LIBLINKLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint32_t data_t;
// 二重リスト
typedef struct cell{
    data_t data;
    struct cell *next;
}Cell;
typedef struct list{
    Cell* head;
    Cell* tail;
    size_t n;
}List;

void errExit(const char* msg);

uint8_t display_list(List* l);

List* init_list();
//uint8_t delete_list(List* l);

// n番目のポインタ (nは0から)
Cell* seek(List* l, size_t n);

uint8_t append_cell(List* l, data_t v);
uint8_t insert_cell(List* l, Cell* c, data_t v);

uint8_t delete_headcell(List* l);
uint8_t delete_tailcell(List* l);
uint8_t delete_nextcell(List* l, Cell* c);
uint8_t delete_cell(List* l, Cell* c);
uint8_t delete_list(List* l);

#endif