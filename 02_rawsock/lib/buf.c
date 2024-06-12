#include <buf.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1550

typedef struct{
    uint8_t v[BUFFER_SIZE];
    size_t len;
}Buffer;


int buffer_init(Buffer *buf){
    memset(buf->v, 0, BUFFER_SIZE);
    if (buf->v == NULL) return -1; // memset err
    buf->len=0;
    return 1;
}
int (*buffer_clear)() = buffer_init; //alias

int buffer_append(Buffer *buf, const uint8_t *data, size_t data_size){
    if (buf->len+data_size>BUFFER_SIZE) return -1; // buffer full
    memcpy(buf->v+buf->len, data, data_size);
    if (buf->v==NULL) return -1; // memcpy err
    buf->len+=data_size;
    return 1;
}

void buffer_print(const Buffer *buf){
    for (int i=0; i<buf->len; i++) printf("%02x ", (buf->v)[i]);
    puts("");
}