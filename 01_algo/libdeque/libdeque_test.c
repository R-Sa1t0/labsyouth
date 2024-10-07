#include "libdeque.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  Deque *dq = deque_init();
  assert(dq != NULL);
  if (dq == NULL)
    exit(1);

  for (int i = 0; i < 5; i++)
    if ((deque_push(dq, dq->head, i)) != true)
      exit(1);
  deque_print(dq);
  puts("");

  for (int i = 0; i < 5; i++)
    if ((deque_push(dq, dq->tail, i)) != true)
      exit(1);
  deque_print(dq);
  puts("");

  for (int i = 0; i < 5; i++) {
    data_t v;
    if ((deque_pop(dq, dq->head, &v)) != true)
      exit(1);
    printf("%u\n", v);
  }
  deque_print(dq);
  puts("");

  for (int i = 0; i < 5; i++) {
    data_t v;
    if ((deque_pop(dq, dq->tail, &v)) != true)
      exit(1);
    printf("%u\n", v);
  }
  deque_print(dq);
  puts("");
}