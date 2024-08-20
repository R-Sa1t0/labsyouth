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
  puts("Hello!");
}