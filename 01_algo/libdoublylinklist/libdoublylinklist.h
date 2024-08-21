#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int32_t data_t;

typedef struct link_node {
  data_t v;
  struct link_node *prev;
  struct link_node *next;
} Node;

// ノードの表示
void display_node(Node *n);
// 初期ノードの作成
Node *node_new(data_t v);
// ノードのつながり削除 (mode: -1で先頭方向すべて、1で末尾方向すべて、0はひとつ)
bool node_delete(int8_t mode, Node *n);
// ノードの全削除 (どこを指定しても先頭まで辿り、そこから消していく)
bool node_delete_all(Node *n);
// シーク(nを起点とし、offset: +で末尾方向, -で先頭方向, INT64_MAXで末尾,
// INT64_MINで先頭)
Node *node_seek(Node *n, int64_t offset);
// ノードの追加 (mode: -1はnの前に追加, 1はnの次に追加)
bool node_add(int8_t mode, Node *n, data_t v);

// ノードの追加(mode: 0で末尾, 1で先頭)
// bool node_append(uint32_t mode, Node *n);
// 1つのノードの削除
// bool node_delete(Node *n);
// ノードの全削除
// void node_deleteall(Node *head);
// データの追加(offset: INT64_MAXで末尾追加, INX32_MINで先頭追加, )