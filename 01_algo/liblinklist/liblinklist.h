#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t data_t;

// Node
typedef struct cell
{
  data_t data;
  struct cell* next;
} Cell;
typedef struct list
{
  Cell* head;
  Cell* tail;
  size_t n;
} List;

// boolにする
uint8_t
display_list(List* l);

List*
init_list();
// uint8_t delete_list(List* l);

// n番目のポインタ (nは0から)
Cell*
seek(List* l, size_t n);

uint8_t
append_cell(List* l, data_t v);
uint8_t
insert_cell(List* l, Cell* c, data_t v);

uint8_t
delete_headcell(List* l);
uint8_t
delete_tailcell(List* l);
uint8_t
delete_nextcell(List* l, Cell* c);
uint8_t
delete_cell(List* l, Cell* c);
uint8_t
delete_list(List* l);