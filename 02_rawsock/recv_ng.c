#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <linux/if_ether.h> // for ETH_P_ALL
#include <string.h>
#include <stdlib.h>


#define BUFFER_SIZE 1550
typedef struct{
    uint8_t v[BUFFER_SIZE];
    size_t len;
}Buffer;
void buffer_init(Buffer *buf){
    memset(buf->v, 0, BUFFER_SIZE);
    buf->len=0;
}
void (*buffer_clear)() = buffer_init; //alias
void buffer_append(Buffer *buf, const uint8_t *data, size_t data_size){
    if (buf->len+data_size>BUFFER_SIZE){
        fprintf(stderr, "BUF_ERR: buffer full\n");
        exit(1);
    }
    memcpy(buf->v+buf->len, data, data_size);
    buf->len+=data_size;
}
void buffer_print(Buffer *buf){
    for (int i=0; i<buf->len; i++) printf("%02x ", ((uint8_t *)buf->v)[i]);
    puts("");
}

int main(void){
    int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }
    Buffer buf;
    buffer_init(&buf);

    while (1){
        ssize_t len = recv(sockfd, buf.v, sizeof(buf.v), 0);
        if (len < 0) {
            fprintf(stderr, "Failed to receive\n");
            return 1;
        }else if (len!=0){
            buf.len = len;
            buffer_print(&buf);
        }
    }
}