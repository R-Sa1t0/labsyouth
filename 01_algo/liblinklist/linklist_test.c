#include <stdio.h>
#include <stdlib.h>

#include "liblinklist.h"

//エラー時のスタックトレースを取りたい
void
errExit(const char* msg)
{
  printf("ERROR: %s\n", msg);
  exit(1);
}
void
warn(const char* msg)
{
  printf("WARN: %s\n", msg);
}

int
main(void)
{
  printf("init\n");
  List* l = init_list();
  if (l == NULL)
    exit(1);
  display_list(l);

  printf("append x5\n");
  for (int32_t i = 0; i < 5; i++) {
    if ((append_cell(l, i)) != true)
      errExit("append_Cell error");
  }
  display_list(l);

  printf("delete_headcell x2\n");
  for (int32_t i = 0; i < 2; i++) {

    if ((delete_headcell(l)) != true)
      errExit("delete_headcell error");
  }
  display_list(l);

  printf("append x4\n");
  for (int32_t i = 99; i < 103; i++) {
    if ((append_cell(l, i)) != true)
      errExit("append_cell error");
  }
  display_list(l);

  printf("insert_cell(l, seek(l, 3), 999)\n");
  if ((insert_cell(l, seek(l, 3), 999)) != true)
    errExit("insert_cell error!");
  display_list(l);

  printf("delete_tailcell x2\n");
  for (int i = 0; i < 2; i++) {
    delete_cell(l, l->tail);
    // if ((delete_tailcell(l)) != true) errExit("delete_tailcell");
  }
  display_list(l);

  printf("delete_nextcell(l, seek(l, 1));\n");
  if ((delete_nextcell(l, seek(l, 1))) != true)
    errExit("delete_nextcell");
  display_list(l);

  printf("delete_nextcell(l, l->head);\n");
  if ((delete_nextcell(l, l->head)) != true)
    errExit("delete_nextcell");
  display_list(l);

  printf("\n\n----------------\n\n");
  delete_cell(l, l->head);
  display_list(l);
  printf("\n\n----------------\n\n");

  printf("delete_list()\n");
  if ((delete_list(l)) != true)
    errExit("delete_list");
  puts("OK");
}