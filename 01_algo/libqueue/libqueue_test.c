#include "../liblinklist/liblinklist.h"
#include "libqueue.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Queue *q = queue_init();
  if (q == NULL)
    exit(1);
  display_cells(q->head);

  for (int i = 0; i < 5; i++)
    if ((push(q, i)) != true)
      break;
  display_cells(q->head);

  data_t v;
  bool stat;
  for (int i = 0; i < 5; i++) {
    stat = pop(q, &v);
    if (stat != true)
      break;
    printf("\nhead: %p, tail: %p, v: %u\n", q->head, q->tail, v);
    display_cells(q->head);
  }

  if ((queue_del(q)) != true)
    exit(1);
}