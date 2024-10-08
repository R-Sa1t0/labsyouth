#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "libdoublylinklist.h"

void node_dump(const Node *node) {
  if (node == NULL) {
    puts("");
    return;
  }

  while (node) {
    printf("prev: %-14p, next: %-14p, addr: %p, v:%u\n", node->prev, node->next,
           node, node->v);

    if (node->prev != NULL && node->prev->next != node) {
      printf("node->prev->next != node\n");
      exit(1);
    }
    if ((node->next != NULL && node->next->prev != node)) {
      printf("node->next->prev != node\n");
    }
    node = node->next;
  }
}

void node_dump_all(const Node *n) { node_dump(node_seek_c(n, INT64_MIN)); }

Node *node_new(data_t v) {
  Node *new = (Node *)malloc(sizeof(Node));
  if (new == NULL)
    return NULL;
  new->next = new->prev = NULL;
  new->v = v;
  return new;
}

void node_delete_one(Node *n) {
  if (n == NULL)
    return;

  if (n->prev != NULL)
    n->prev->next = n->next;
  if (n->next != NULL)
    n->next->prev = n->prev;

  free(n);
}

void node_delete_after(Node *n) {
  if (n == NULL)
    return;

  while (n) {
    Node *tmp = n;
    n = n->next;
    node_delete_one(tmp);
  }
}

Node *node_seek(Node *n, const int64_t offset) {
  if (n == NULL)
    return NULL;

  if (offset == INT64_MAX) {
    while (n->next) {
      n = n->next;
    }
    return n;
  }
  if (offset == INT64_MIN) {
    while (n->prev) {
      n = n->prev;
    }
    return n;
  }

  for (int64_t i = 0; i < llabs(offset); i++) {
    if (n == NULL)
      return NULL;
    if (offset > 0) {
      n = n->next;
    } else {
      n = n->prev;
    }
  }
  return n;
}

const Node *node_seek_c(const Node *n, const int64_t offset) {
  return node_seek((Node *)n, offset);
}

Node *node_insert(Node *n, data_t v) {
  if (n == NULL)
    return NULL;
  Node *new = node_new(v);
  if (new == NULL)
    return NULL;

  new->prev = n;
  new->next = n->next;
  if (n->next != NULL)
    n->next->prev = new;
  n->next = new;

  return new;
}

Node *node_insert_before(Node *n, data_t v) {
  if (n == NULL)
    return NULL;
  Node *new = node_new(v);
  if (new == NULL)
    return NULL;

  new->prev = n->prev;
  new->next = n;
  if (n->prev != NULL)
    n->prev->next = new;
  n->prev = new;

  return new;
}