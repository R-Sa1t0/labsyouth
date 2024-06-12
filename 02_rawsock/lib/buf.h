#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1550

typedef struct{
    uint8_t v[BUFFER_SIZE];
    size_t len;
}Buffer;

int buffer_init(Buffer *buf);
int buffer_append(Buffer *buf, const uint8_t *data, size_t data_size);
void buffer_print(const Buffer *buf);