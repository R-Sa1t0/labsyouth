#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <linux/if_ether.h> // for ETH_P_ALL

int mac_check(int offset, uint8_t *buf, uint8_t *mac){
    for(int i=0; i<6; i++){
        if (buf[offset+i] != mac[i]){
            return 0;
        }
    }
    return 1;
}

void packet_processing(uint8_t *buf, ssize_t len){
    for (int i=0; i<len; i++){
        printf("%02x ", buf[i]);
    }
    
    printf("\n\n");
}

int main(void){
    int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }
    uint8_t buf[1550];

    while (1){
        ssize_t len = recv(sockfd, buf, sizeof(buf), 0);
        if (len < 0) {
            fprintf(stderr, "Failed to receive\n");
            return 1;
        }else if (len!=0){
            packet_processing(buf, len);
        }
    }
}