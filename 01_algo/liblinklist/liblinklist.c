#include "liblinklist.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void display_cells(const Cell *cell) {
  while (cell != NULL) {
    printf("addr: %p, data: %d, next: %p\n", cell, cell->data, cell->next);
    cell = cell->next;
  }
}

// Cell_newがいいかも
Cell *cell_init(data_t v) {
  Cell *new_cell = (Cell *)malloc(sizeof(Cell));
  if (new_cell == NULL)
    return NULL;
  new_cell->data = v;
  new_cell->next = NULL;
  return new_cell;
}

Cell *cell_append(Cell *c, data_t v) {
  if (c == NULL || c->next != NULL)
    return NULL;

  Cell *new = cell_init(v);
  if (new == NULL)
    return NULL;

  c->next = new;

  return new;
}

void cell_delete_and_seek_next(Cell **c) {
  Cell *tmp = *c;
  *c = (*c)->next;
  free(tmp);
}

void cell_alldelete(Cell *head) {
  while (head) {
    cell_delete_and_seek_next(&head);
  }
}
