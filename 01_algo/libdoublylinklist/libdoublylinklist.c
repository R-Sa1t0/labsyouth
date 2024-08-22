#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libdoublylinklist.h"

void display_node(const Node *node) {
  if (node == NULL)
    return;
  Node *n = node_seek(node, INT64_MIN);
  while (n) {
    printf("addr: %p, v: %u, prev: %p, next: %p\n", n, n->v, n->prev, n->next);
    n = n->next;
  }
}

Node *node_new(data_t v) {
  Node *new = (Node *)malloc(sizeof(Node));
  if (new == NULL)
    return NULL;
  new->next = new->prev = NULL;
  new->v = v;
  return new;
}

void node_delete_one(Node *n) {
  n->prev->next = n->next;
  n->next->prev = n->prev;
  free(n);
}

bool node_delete(int8_t mode, Node *n) {
  if (n == NULL)
    return false;
  else if (mode == -1) {
    n->next->prev = NULL;
    while (n) {
      Node *tmp = n;
      n = n->prev;
      free(tmp);
    }
  } else if (mode == 1) {
    if (n != NULL && n->prev != NULL)
      n->prev->next = NULL;
    while (n) {
      Node *tmp = n;
      n = n->next;
      free(tmp);
    }
  } else if (mode == 0) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    free(n);
  } else {
    return false;
  }
  return true;
}

bool node_delete_all(Node *n) {
  if (n == NULL)
    return false;

  Node *head_ptr = node_seek(n, INT64_MIN);

  bool stat = node_delete(1, head_ptr);
  if (stat != true)
    return false;

  return true;
}

Node *node_seek(Node *n, const int64_t offset) {
  if (n == NULL)
    return NULL;

  if (offset == INT64_MAX)
    while (n->next)
      n = n->next;
  else if (offset == INT64_MIN)
    while (n->prev)
      n = n->prev;
  else {
    for (int64_t i = 0; i < llabs(offset); i++) {
      if (n == NULL)
        return NULL;
      else if (offset > 0)
        n = n->next;
      else
        n = n->prev;
    }
  }
  return n;
}

Node *node_insert(Node *n, data_t v) {
  if (n == NULL)
    return NULL;
  Node *new = node_new(v);
  if (new == NULL)
    return NULL;

  new->next = n->next;
  new->prev = n;
  n->next = new;
  if (n->next != NULL)
    n->next->prev = new;

  return new;
}

bool node_add(int8_t mode, Node *n, data_t v) {
  if (n == NULL)
    return false;

  Node *new = node_new(v);
  if (mode == -1) {
    if (n->prev != NULL) {
      new->prev = n->prev;
      new->next = n;
      n->prev->next = new;
      n->prev = new;
    } else {
      new->prev = NULL;
      new->next = n;
      n->prev = new;
    }
  } else if (mode == 1) {
    if (n->next != NULL) {
      new->prev = n;
      new->next = n->next;
      n->next->prev = new;
      n->next = new;
    } else {
      new->next = NULL;
      new->prev = n;
      n->next = new;
    }
  } else {
    free(new);
    return false;
  }
  return true;
}