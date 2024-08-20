#pragma once

#include "../liblinklist/liblinklist.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
  Cell *head;
} Stack;

// Stackの初期化 (空のスタックへのポインタを返す)
Stack *stack_init();
// Stackの全削除
void stack_delete(Stack *s);

// Stackへのデータ追加
bool push(Stack *s, data_t v);
// Stackのデータ読み出し
bool pop(Stack *s, data_t *v);