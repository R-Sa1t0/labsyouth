#include "libbuf.h"
#include <assert.h>
#include <stdio.h>

int main() {
  Buf *b = buf_init();
  print_buf(b);
  puts("OK");
}