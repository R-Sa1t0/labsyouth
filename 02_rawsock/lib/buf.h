#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct Buffer;

int buffer_init(Buffer *buf);
int buffer_append(Buffer *buf, const uint8_t *data, size_t data_size);
void buffer_print(const Buffer *buf);