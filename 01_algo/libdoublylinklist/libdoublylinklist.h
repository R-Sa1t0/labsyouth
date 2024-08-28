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

// デバッグ用ダンプ出力
void dump_node(const Node *n);
// 必要であればdump_all(先頭までたどって表示)を作る
void dump_all(const Node *n);

// シーク(nを起点とし、offset: +で末尾方向, -で先頭方向, INT64_MAXで末尾,
// INT64_MINで先頭)
Node *node_seek(Node *n, int64_t offset);
const Node *node_seek_c(const Node *n, const int64_t offset);

// 初期ノードの作成
Node *node_new(data_t v);
// 指定したノードの次に、ノードを1つ挿入する
Node *node_insert(Node *n, data_t v);
// 指定したノードの前に、ノードを1つ挿入する
Node *node_insert_before(Node *n, data_t v);

// ノードを1つ削除
void node_delete_one(Node *n);
// ノードの削除 (指定したポインタから先を削除)
bool node_delete_after(Node *n);
// node_delete_before()は必要になったら実装する