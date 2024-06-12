#include <stdio.h>
#include <stdlib.h> // exit(), EXIT_FAILURE
#include <errno.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <linux/if_ether.h> // for ETH_P_ALL
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#include "lib/buf.h"

#define NIC_NAME "N2-C2"

int main(void){
    int sockfd =0;

    struct ifreq ifr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        exit(EXIT_FAILURE);
    }
    strncpy(ifr.ifr_name, NIC_NAME, IFNAMSIZ - 1);
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1) {
        fprintf(stderr, "ioctl SIOCGIFINDEX failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_ll addr;
    memset(&addr, 0x00, sizeof(addr));
    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(ETH_P_ALL);
    addr.sll_ifindex = ifr.ifr_ifindex;
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "bind failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
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