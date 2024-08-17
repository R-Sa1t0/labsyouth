#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t data_t;

// Node
typedef struct node {
  data_t data;
  struct node *next;
} Cell;
typedef struct list {
  Cell *head;
  Cell *tail;
  size_t n;
} List;

// Cellの表示
bool display_cells(const Cell *head);
// Cellの初期化
Cell *cell_init(data_t v);
// Cellの追加 (追加したCellのポインタを返す)
Cell *cell_append(Cell *c, data_t v);
// Cellの削除 (Cell->nextを返す)
Cell *cell_delete(Cell *c);

// Listの表示
bool display_list(const List *l);
// Listの初期化
List *init_list();
// Listの削除
uint8_t delete_list(List *l);
// List内のn番目のポインタの取得 (nは0から)
Cell *seek(List *l, size_t n);
// Listへ要素追加
uint8_t list_append(List *l, data_t v);
// Listへ要素挿入
uint8_t list_insert(List *l, Cell *c, data_t v);
// Listの要素削除
uint8_t list_delete_cell(List *l, Cell *c);