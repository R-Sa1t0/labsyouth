#include "util.h"

// todo : strncpy の安全バージョンを実装する
// todo : defile noerrorを作る

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

int parse_macaddr(struct ether_addr *addr, const char *addr_str) {
    unsigned int octets[6];
    if (sscanf(addr_str, "%x:%x:%x:%x:%x:%x", 
               &octets[0], &octets[1], &octets[2], 
               &octets[3], &octets[4], &octets[5]) == 6) {
        for (int i = 0; i < 6; i++) {
            addr->ether_addr_octet[i] = (uint8_t)octets[i];
        }
        return 0;
    }
    return -1;
}

int open_rawsock_pernic(int *fd, const char* nic_name){
    struct ifreq ifr;
    printf("ok-rawsock\n");
    *fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (*fd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return -1;
    }
    strncpy(ifr.ifr_name, nic_name, IFNAMSIZ - 1);
    if (ioctl(*fd, SIOCGIFINDEX, &ifr) == -1) {
        fprintf(stderr, "ioctl SIOCGIFINDEX failed: %s\n", strerror(errno));
        return -2;
    }

    *fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (*fd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        return -3;
    }

    struct sockaddr_ll addr;
    memset(&addr, 0x00, sizeof(addr));
    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(ETH_P_ALL);
    addr.sll_ifindex = ifr.ifr_ifindex;
    if (bind(*fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "bind failed: %s\n", strerror(errno));
        return -4;
    }

    return 0;
}
