#include <stdio.h>
#include <stdlib.h>

#include "../liblinklist/liblinklist.h"
#include "libstack.h"

int main(void) {
  Stack *s = stack_init();
  if (s == NULL)
    exit(1);
  display_cells(s->head);

  for (int i = 0; i < 5; i++)
    if ((push(s, i)) != true)
      exit(1);
  display_cells(s->head);

  data_t v;
  bool stat;
  for (int i = 0; i < 5; i++) {
    stat = pop(s, &v);
    if (stat != true)
      break;
    printf("v: %u\n", v);
  }
  stack_delete(s);
}