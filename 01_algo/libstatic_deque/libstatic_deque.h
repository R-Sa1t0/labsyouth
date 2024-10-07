#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef int data_t;
typedef struct d_node {
  data_t v;
  struct d_node *next;
  struct d_node *prev;
} Node;
typedef struct deque {
  size_t size;
  d_node *head;
  d_node *tail;
} Deque;

void deque_print(Deque *q);
Deque *deque_init(size_t size);

bool deque_push(Deque *q, Node *n, data_t v);
bool deque_pop(Deque *q, Node *n, data_t *v);