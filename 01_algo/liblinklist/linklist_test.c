#include <stdio.h>
#include <stdlib.h>

#include "liblinklist.h"

typedef struct list {
  Cell *head;
  Cell *tail;
} List;

//エラー時のスタックトレースを取りたい
void errExit(const char *msg) {
  printf("ERROR: %s\n", msg);
  exit(1);
}

void warn(const char *msg) { printf("WARN: %s\n", msg); }

int main(void) {
  List *l = (List *)malloc(sizeof(List));
  l->head = l->tail = NULL;
  display_cells(l->head);

  Cell *new = cell_init(0);
  if (new == NULL)
    errExit("cell_init");
  l->head = l->tail = new;
  display_cells(l->head);
  puts("");

  Cell *tmp = NULL;
  for (int i = 1; i < 5; i++) {
    tmp = cell_append(l->tail, i);
    if (tmp == NULL)
      errExit("Cell_append");
    l->tail = tmp;
  }
  display_cells(l->head);
  puts("");

  for (int i = 1; i < 5; i++) {
    tmp = cell_init(i);
    if (tmp == NULL)
      errExit("Cell_init");
    tmp->next = l->head;
    l->head = tmp;
  }
  display_cells(l->head);
  puts("");

  cell_alldelete(l->head);
  l->head = l->tail = NULL;
  display_cells(l->head);
}