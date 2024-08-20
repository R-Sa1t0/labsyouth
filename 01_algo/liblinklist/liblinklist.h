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

// Cellの表示
void display_cells(const Cell *head);
// Cellの初期化
Cell *cell_init(data_t v);
// Cellの追加 (追加したCellのポインタを返す / cはNULLではいけない / Cはリスト末尾である必要がある) 
Cell *cell_append(Cell *c, data_t v);
// Cellの全削除
void cell_alldelete(Cell *head);
/*
実装メモ : 
1:
途中{のノードを削除, にノード挿入}する関数を実装すると
 - 指定したアドレスの次のノードを削除する
 - 指定したアドレスの次にノードを挿入する
という仕様になり、これらは使いにくいので、実装がはしない

2: 
先頭または末尾のノード削除はやることが単純(freeするだけ)なのでAPIに追加しない
*/
