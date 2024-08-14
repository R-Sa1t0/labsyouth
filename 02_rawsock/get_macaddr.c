
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>

#define INTERFACE_NAME "ens33"

int main(int argc, char *argv[])
{
    struct ifreq ifr = {};
    int sock_fd;
    char mac_addr[18];

    // ソケットを開く
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }

    // インターフェース名をコピー
    strncpy(ifr.ifr_name, INTERFACE_NAME, IFNAMSIZ - 1);

    // MACアドレスを取得
    if (ioctl(sock_fd, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl");
        close(sock_fd);
        return 1;
    }
    close(sock_fd);

    for(int i=0; i<6; i++){
        fprintf(stdout, "%02X", (uint8_t)ifr.ifr_hwaddr.sa_data[i]);
        if (i!=5) fprintf(stdout, ":");
    }
    puts("");

    return 0;
}