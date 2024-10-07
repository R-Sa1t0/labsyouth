
#include "libstatic_deque.h"

#include <stdio.h>
#include <stdlib.h>

void deque_print(Deque *dq) {
  printf("head: %p, tail: %p\n", dq->head, dq->tail);
  if (dq->head != NULL)
    node_dump(dq->head);
}

Deque *deque_init(size_t size) {
  Deque *dq = (Deque *)malloc(sizeof(Deque));
  if (dq == NULL)
    return NULL;
  Node *new_node = (Node *)malloc(size*sizeof(Node));
  if (new_node == NULL)
    return NULL;
  dq->head = dq->tail = NULL;
  dq->size = size;
  return dq;
}

