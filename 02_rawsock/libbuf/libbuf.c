#include "libbuf.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool print_buf(Buf *b) {
  if (b == NULL)
    return false;
  fprintf(stdout, "len: %zu, ", b->len);
  fprintf(stdout, "next: %p, ", b->next);
  for (int i = 0; i < BUF_SIZE; i++)
    fprintf(stdout, "%02x ", b->v[i]);
  puts("");
  return false;
}

Buf *buf_init() {
  Buf *new_buf = (Buf *)malloc(sizeof(Buf));
  if (new_buf == NULL)
    return NULL;
  new_buf->next = NULL;
  new_buf->len = 0;
  memset(new_buf->v, 0, sizeof(new_buf->v));
  return new_buf;
}

bool push() { return false; }

bool pop() { return false; }