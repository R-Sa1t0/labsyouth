#include <stdio.h>
#include <stdlib.h>

#include "libdoublylinklist.h"

int main() {
  Node *center = node_new(0);
  display_node(center);
  puts("");

  if ((node_add(1, center, 1)) != true)
    exit(1);
  display_node(center);
  puts("");

  if ((node_add(-1, center, 1)) != true)
    exit(1);
  display_node(center);
  puts("");

  for (int i = 2; i < 5; i++)
    if ((node_add(1, node_seek(center, INT64_MAX), i)) != true)
      exit(1);
  display_node(center);
  puts("");

  for (int i = 2; i < 5; i++)
    if ((node_add(-1, node_seek(center, INT64_MIN), i)) != true)
      exit(1);
  display_node(center);
  puts("");

  if ((node_delete(1, node_seek(center, 3))) != true)
    exit(1);
  display_node(center);
  puts("");

  if ((node_delete(-1, node_seek(center, -3))) != true)
    exit(1);
  display_node(center);
  puts("");
#if 0
  node_delete_one(center->next);
  display_node(center);
  puts("");

  if ((node_insert(center, 1)) == NULL)
    exit(1);
  display_node(center);
  puts("");

  if ((node_insert(center->next->next, 3)) == NULL)
    exit(1);
  display_node(center);
  puts("");


  node_delete_one(node_seek(center, INT64_MAX));
  display_node(center);
  puts("");
#else
#endif

  if ((node_delete_all(center)) != true)
    puts("err");
}