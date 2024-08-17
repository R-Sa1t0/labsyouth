#include <stdio.h>
#include <stdlib.h>

#include "liblinklist.h"

//エラー時のスタックトレースを取りたい
void errExit(const char *msg) {
  printf("ERROR: %s\n", msg);
  exit(1);
}
void warn(const char *msg) { printf("WARN: %s\n", msg); }

int main(void) {
  printf("init\n");
  List *l = init_list();
  if (l == NULL)
    exit(1);
  display_list(l);

  printf("append x5\n");
  for (int32_t i = 0; i < 5; i++) {
    if ((list_append(l, i)) != true)
      errExit("append_Cell error");
  }
  display_list(l);

  printf("append x4\n");
  for (int32_t i = 99; i < 103; i++) {
    if ((list_append(l, i)) != true)
      errExit("list_append error");
  }
  display_list(l);

  printf("list_insert(l, seek(l, 3), 999)\n");
  if ((list_insert(l, seek(l, 3), 999)) != true)
    errExit("list_insert error!");
  display_list(l);

  printf("delete_tailcell x2\n");
  for (int i = 0; i < 2; i++) {
    list_delete_cell(l, l->tail);
    // if ((delete_tailcell(l)) != true) errExit("delete_tailcell");
  }
  display_list(l);

  printf("\n\n----------------\n\n");
  list_delete_cell(l, l->head);
  display_list(l);
  printf("\n\n----------------\n\n");

  printf("delete_list()\n");
  if ((delete_list(l)) != true)
    errExit("delete_list");
  puts("OK");
}