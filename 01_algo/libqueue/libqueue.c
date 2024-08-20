#include "libqueue.h"
#include "../liblinklist/liblinklist.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Queue *queue_init() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  if (q == NULL)
    return NULL;
  q->head = q->tail = NULL;
  return q;
}

void queue_del(Queue *q) {
  if (q == NULL)
    return;
  
  cell_alldelete(q->head);
  free(q);
}

bool push(Queue *q, data_t v) {
  if (q == NULL)
    return false;

  if (q->head == NULL && q->tail == NULL) {
    Cell *new = cell_init(v);
    if (new == NULL)
      return false;
    q->head = q->tail = new;
  } else {
    Cell *new = cell_append(q->tail, v);
    if (new == NULL)
      return false;
    q->tail = new;
  }

  return true;
}

bool pop(Queue *q, data_t *v) {
  if (q == NULL || q->head == NULL || q->tail == NULL)
    return false;

  *v = q->head->data;

  Cell *tmp = q->head;
  q->head = q->head->next;
  free(tmp);

  return true;
}