#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <linux/if_ether.h> // for ETH_P_ALL

int mac_check(int offset, unsigned char *buf, unsigned char *mac){
    for(int i=0; i<6; i++){
        if (buf[offset+i] != mac[i]){
            return 0;
        }
    }
    return 1;
}

void packet_processing(unsigned char *buf, ssize_t len){
    // wan-side nic mac addr
    unsigned char node_mac_dst[6] = {0x9e, 0xd0, 0x9e, 0x53, 0x3d, 0xb2};
    // if dst or src mac is not for me, return
    if (mac_check(0, buf, node_mac_dst) == 0
        && mac_check(6, buf, node_mac_dst) == 0) return;

    // ethertype is not 0x86dd, return
    if (buf[12] != 0x86 || buf[13] != 0xdd) return;
    // ipv6 next header is not 43 (routing header), return
    if (buf[20] != 43) return;

    // print sid
    uint8_t sid[16];
    for(int i=0; i<16; i++){
        sid[i] = buf[14+40+8+i];
    }
    printf("Received SRv6 Packet! (%ld bytes)\n", len);
    printf("SID: ");
    for(int i=0; i<16; i++){
        printf("%02x ", sid[i]);
    }
    puts("");
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
    unsigned char buf[1550];

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