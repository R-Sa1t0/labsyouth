#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../liblinklist/liblinklist.h"
#include "libstack.h"

Stack *stack_init() {
  Stack *new = (Stack *)malloc(sizeof(Stack));
  if (new == NULL)
    return NULL;
  new->head = NULL;
  return new;
}

void stack_delete(Stack *s) {
  if (s == NULL)
    return;

  cell_alldelete(s->head);
  free(s);

  return;
}

bool push(Stack *s, data_t v) {
  if (s == NULL)
    return false;

  if (s->head == NULL) {
    Cell *new = cell_init(v);
    if (new == NULL)
      return false;
    s->head = new;
  } else {
    Cell *new = cell_init(v);
    if (new == NULL)
      return false;
    new->next = s->head;
    s->head = new;
  }

  return true;
}

bool pop(Stack *s, data_t *v) {
  if (s->head == NULL)
    return false;

  *v = s->head->data;

  Cell *tmp = s->head;
  s->head = s->head->next;
  free(tmp);

  return true;
}