#pragma once

#include "../liblinklist/liblinklist.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
  Cell *head;
  Cell *tail;
} Stack;

Stack *stack_init();
bool stack_delete(Stack *s);

bool push(Stack *s, data_t v);
bool pop(Stack *s, data_t *v);
