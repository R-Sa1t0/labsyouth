#include "libqueue.h"
#include "../liblinklist/liblinklist.h"

#include <stdio.h>
#include <stdlib.h>

Queue *queue_init() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  if (q == NULL)
    return NULL;
  q->head = q->tail = NULL;
  return q;
}

bool queue_del(Queue *q) {
  while (true) {
    if (q->head == NULL) {
      q->head = NULL;
      break;
    }
    q->head = cell_delete(q->head);
  }

  free(q);
  q = NULL;

  return true;
}

bool push(Queue *q, data_t v) {
  if (q == NULL)
    return false;

  if (q->head == NULL && q->tail == NULL) {
    Cell *new = cell_init(v);
    q->head = q->tail = new;
    return true;
  }

  Cell *new = cell_append(q->tail, v);
  if (new == NULL)
    return false;
  q->tail = new;

  return true;
}

bool pop(Queue *q, data_t *v) {
  if (q->head == NULL || q->tail == NULL)
    return false;

  *v = q->head->data;

  q->head = cell_delete(q->head);
  if (q->head == NULL) {
    q->tail = NULL;
  }

  return true;
}