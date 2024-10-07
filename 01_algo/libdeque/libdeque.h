#pragma once

#include "../libdoublylinklist/libdoublylinklist.h"
#include <stdbool.h>

typedef struct link_node d_node;
typedef struct deque {
  d_node *head;
  d_node *tail;
} Deque;

void deque_print(Deque *q);
Deque *deque_init();

bool deque_push(Deque *q, d_node *dn, data_t v);
bool deque_pop(Deque *q, d_node *dn, data_t *v);