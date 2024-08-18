#pragma once

#include "../liblinklist/liblinklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct queue {
  Cell *head;
  Cell *tail;
} Queue;

Queue *queue_init();
bool queue_del(Queue *q);

bool push(Queue *q, data_t v);
bool pop(Queue *q, data_t *v);