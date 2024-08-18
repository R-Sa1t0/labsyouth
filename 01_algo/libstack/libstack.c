#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../liblinklist/liblinklist.h"
#include "libstack.h"

Stack *stack_init() {
  Stack *new = (Stack *)malloc(sizeof(Stack));
  if (new == NULL)
    return NULL;
  new->head = new->tail = NULL;
  return new;
}

bool stack_delete(Stack *s) {
  while (true) {
    if (s->head == NULL) {
      s->tail = NULL;
      break;
    }
    s->head = cell_delete(s->head);
  }

  free(s);
  s = NULL;

  return true;
}

bool push(Stack *s, data_t v) {
  if (s == NULL)
    return false;

  if (s->head == NULL && s->tail == NULL) {
    Cell *new = cell_init(v);
    if (new == NULL)
      return false;
    s->head = s->tail = new;
  } else {
    Cell *new = cell_append(NULL, v);
    if (new == NULL)
      return false;
    new->next = s->head;
    s->head = new;
  }

  return true;
}

bool pop(Stack *s, data_t *v) {
  if (s->head == NULL && s->tail == NULL)
    return false;

  *v = s->head->data;
  s->head = cell_delete(s->head);
  if (s->head == NULL) {
    s->tail = NULL;
  }

  return true;
}