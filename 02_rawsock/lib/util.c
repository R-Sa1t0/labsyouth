#include "util.h"

int get_lladdr(struct ether_addr *addr, const char *nic_name){
    struct ifreq ifr;

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return sock_fd;
    }
    
    if (strlen(nic_name) < IFNAMSIZ) {
        strcpy(ifr.ifr_name, nic_name);
    } else {
        strncpy(ifr.ifr_name, nic_name, IFNAMSIZ - 1);
        ifr.ifr_name[IFNAMSIZ - 1] = '\0';
    }
    //strncpy(ifr.ifr_name, nic_name, IFNAMSIZ - 1);

    if (ioctl(sock_fd, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl");
        close(sock_fd);
        return sock_fd;
    }
    close(sock_fd);

    for (int i=0; i<6; i++){
        addr->ether_addr_octet[i]=(uint8_t)ifr.ifr_hwaddr.sa_data[i];
    }
    return 0;
}