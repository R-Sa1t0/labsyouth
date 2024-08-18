#include "liblinklist.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool display_cells(const Cell *head) {
  if (head == NULL)
    return false;

  Cell *temp = (Cell *)head;
  while (temp != NULL) {
    printf("addr: %p, data: %d, next: %p\n", temp, temp->data, temp->next);
    temp = temp->next;
  }

  return true;
}

Cell *cell_init(data_t v) {
  Cell *new_cell = (Cell *)malloc(sizeof(Cell));
  if (new_cell == NULL)
    return NULL;
  new_cell->data = v;
  new_cell->next = NULL;
  return new_cell;
}

Cell *cell_delete(Cell *c) {
  Cell *next = c->next;
  free(c);
  return next;
}

bool display_list(const List *l) {
  printf("head: %p, tail: %p, len: %zu\n", l->head, l->tail, l->n);
  if ((display_cells(l->head)) != true)
    return false;

  Cell *c = l->head;
  size_t n = 0;
  while (c != NULL) {
    c = c->next;
    n++;
  }
  if (n != l->n) {
    printf("ERROR : n != l->n, n: %zu\n", n);
    return false;
  }

  puts("");
  return true;
}

List *init_list() {
  List *l = (List *)malloc(sizeof(List));
  if (l == NULL)
    return NULL;

  l->head = l->tail = NULL;
  l->n = 0;
  return l;
}

bool delete_list(List *l) {
  if (l->head == NULL) {
    return false;
  } else if (l->tail == NULL) {
    return false;
  } else {
    while (true) {
      l->head = cell_delete(l->head);
      l->n--;
      if (l->head == NULL) {
        l->head = l->tail = NULL;
        l->n = 0;
        break;
      }
    }
  }
  free(l);
  l = NULL;

  return true;
}

Cell *seek(List *l, size_t n) {
  if (n == 0)
    return l->head;

  Cell *c = l->head;
  size_t len = 0;

  while (c != NULL) {
    if (len == n)
      return c;

    c = c->next;
    len++;
  }

  return NULL;
}

bool list_append(List *l, data_t v) {
  Cell *nc = (Cell *)malloc(sizeof(Cell));
  if (nc == NULL)
    return false;
  nc->data = v;
  nc->next = NULL;

  if (l->head == NULL) {
    l->head = l->tail = nc;
  } else {
    l->tail->next = nc;
    l->tail = nc;
  }

  l->n++;

  return true;
}

bool list_insert(List *l, Cell *c, data_t v) {
  Cell *nc = cell_init(v);
  if (nc == NULL)
    return false;

  nc->next = c->next;
  c->next = nc;

  l->n++;

  return true;
}

bool list_delete_cell(List *l, Cell *c) {
  if (l == NULL || c == NULL) {
    return false;
  }

  if (c == l->head) {
    l->head = cell_delete(l->head);
    if (l->head == NULL) {
      l->tail = NULL;
    }
  } else {
    Cell *current = l->head;
    while (current != NULL && current->next != c) {
      current = current->next;
    }
    if (current != NULL) {
      current->next = cell_delete(current->next);
      if (current->next == NULL) {
        l->tail = current;
      }
    } else {
      return false;
    }
  }

  l->n--;
  return true;
}
