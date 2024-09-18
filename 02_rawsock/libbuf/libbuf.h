#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1550

typedef struct buf_node {
  uint8_t v[BUF_SIZE];
  size_t len;
  struct buf *next;
} Buf;

bool print_buf(Buf *b);