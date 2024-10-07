#pragma once

#include "../liblinklist/liblinklist.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
  Cell *head;
  Cell *tail;
} Queue;

// 初期化 (空のキューへのポインタを返す)
Queue *queue_init();
// キューの削除
void queue_del(Queue *q);

// キューへのデータ追加
bool push(Queue *q, data_t v);
// キューからのデータ取り出し (falseの場合はvにデータが入っていない)
bool pop(Queue *q, data_t *v);