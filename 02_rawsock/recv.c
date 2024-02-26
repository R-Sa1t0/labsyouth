#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>

int main(void){
    int sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return 1;
    }
    unsigned char buf[1550];

    while (1){
        ssize_t len = recv(sockfd, buf, sizeof(buf), 0);
        if (len < 0) {
            fprintf(stderr, "Failed to receive\n");
            return 1;
        }
        if (len!=0){
            printf("Received %ld bytes\n", len);
            for(int i=0; i<len; i++){
                printf("%02x ", buf[i]);
            }
            printf("\n\n");
        }
    }
}