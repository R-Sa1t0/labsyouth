#include "libdeque.h"
#include "../libdoublylinklist/libdoublylinklist.h"

#include <stdio.h>
#include <stdlib.h>

void deque_print(Deque *dq) {
  printf("head: %p, tail: %p\n", dq->head, dq->tail);
  if (dq->head != NULL)
    node_dump(dq->head);
}

Deque *deque_init() {
  Deque *dq = (Deque *)malloc(sizeof(Deque));
  if (dq == NULL)
    return NULL;
  dq->head = dq->tail = NULL;
  return dq;
}

bool deque_push(Deque *q, d_node *dn, data_t v) {
  d_node *new_node_addr;
  if (q->head == NULL && q->tail == NULL) {
    new_node_addr = node_new(v);
    if (new_node_addr == NULL)
      return false;
    q->head = q->tail = new_node_addr;
    return true;
  }
  if (dn == q->head) {
    new_node_addr = node_insert_before(dn, v);
    if (new_node_addr == NULL)
      return false;
    q->head = new_node_addr;
    return true;
  } else if (dn == q->tail) {
    new_node_addr = node_insert(dn, v);
    if (new_node_addr == NULL)
      return false;
    q->tail = new_node_addr;
    return true;
  } else {
    return false;
  }
}

bool deque_pop(Deque *dq, d_node *dn, data_t *v) {
  if (dq->head == NULL && dq->tail == NULL)
    return false;
  if (dq->head == NULL || dq->tail == NULL)
    return false;

  if (dq->head == dq->tail) {
    *v = dq->head->v;
    node_delete_one(dq->head);
    dq->head = dq->tail = NULL;
    return true;
  }

  if (dn == dq->head) {
    *v = dq->head->v;
    d_node *tmp = dq->head;
    dq->head = dq->head->next;
    dq->head->prev = NULL;
    node_delete_one(tmp);
    return true;
  }
  if (dn == dq->tail) {
    *v = dq->tail->v;
    d_node *tmp = dq->tail;
    dq->tail = dq->tail->prev;
    dq->tail->next = NULL;
    node_delete_one(tmp);
    return true;
  }
  return false;
}