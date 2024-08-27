#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "libdoublylinklist.h"

int main() {
  // node_new
  Node *center = node_new(0);
  assert(center != NULL);
  if (center == NULL) 
    exit(1);

  // node_insert
  if (node_insert(center, 1) == NULL)
    exit(1);
  display_node(center);
  puts("");

  // node_insert_before
  if (node_insert_before(center, 1) == NULL)
    exit(1);
  display_node(center);
  puts("");

  // node_seek
  printf("head: %p\n", node_seek(center, INT64_MIN));
  printf("tail: %p\n", node_seek(center, INT64_MAX));
  puts("");

  // node_delete_one(head)
  node_delete_one(center->next);
  display_node(center);
  puts("");

  // node_delete_one(tail)
  node_delete_one(center->prev);
  display_node(center);
  puts("");

  // node_delete_all
  if ((node_delete_all(center)) != true)
    puts("err");
}