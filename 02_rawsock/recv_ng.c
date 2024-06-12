#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <linux/if_ether.h> // for ETH_P_ALL
#include <string.h>
#include <stdlib.h>

#include "lib/buf.h"

int main(void){
    int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }
    Buffer buf;
    if ((buffer_init(&buf))!=0) exit(1);

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