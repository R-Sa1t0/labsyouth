#include <stdio.h>  //fprintf()
#include <stdint.h>  //uint8_t
#include <stdlib.h>  //exit()
#include <errno.h>  // errno
#include <string.h>  //memset()
#include <unistd.h>  //close()

#include <linux/in6.h>  //struct in6_addr
#include <net/ethernet.h>  //struct ether_addr, struct eth_header
#include <netinet/ip6.h> // struct ip6_hdr
#include <linux/seg6.h> // srv6 hdr
#include <arpa/inet.h>  //inet_pton()
#include <sys/ioctl.h>  //ioctl()
#include <net/if.h>  //struct ifreq
#include <linux/if_packet.h> //sockaddr_ll

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

struct ether_addr get_macaddr(const char *nic_name){
    struct ifreq ifr;
    struct ether_addr addr;

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    strncpy(ifr.ifr_name, nic_name, IFNAMSIZ - 1);

    if (ioctl(sock_fd, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    close(sock_fd);

    for (int i=0; i<6; i++){
        addr.ether_addr_octet[i]=(uint8_t)ifr.ifr_hwaddr.sa_data[i];
    }

    return addr; 
}

int parse_macaddr(struct ether_addr *addr,const char *addr_str){
    if (sscanf(addr_str, "%x:%x:%x:%x:%x:%x", 
        addr->ether_addr_octet[0], addr->ether_addr_octet[1],
        addr->ether_addr_octet[2], addr->ether_addr_octet[3],
        addr->ether_addr_octet[4], addr->ether_addr_octet[5])==6){
    }else{
        return -1;
    }
    return 1;
}

typedef struct {
    struct in6_addr ip6_srcaddr;
    struct in6_addr ip6_dstaddr;
    char *lan_nic_name;
    char *wan_nic_name;
    struct ether_addr lan_mac;
    struct ether_addr wan_mac;
    struct ether_addr dst_mac;
}arg;
arg parse_arg(int argc, char *argv[]){
    arg result;
    if (argc != 6) {
        fprintf(stderr, "Usage: %s [srcaddr] [dstaddr] [lan-side-nic-name] [wan-side-nic-name] [dst mac addr]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (inet_pton(AF_INET6, argv[1], &result.ip6_srcaddr) != 1) {
        fprintf(stderr, "Invalid source IPv6 address: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (inet_pton(AF_INET6, argv[2], &result.ip6_dstaddr) != 1) {
        fprintf(stderr, "Invalid destination IPv6 address: %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    result.lan_nic_name = strdup(argv[3]);
    if (result.lan_nic_name == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    result.wan_nic_name = strdup(argv[4]);
    if (result.wan_nic_name == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    if ((parse_macaddr(&result.dst_mac, argv[5]))!=1) {
        fprintf(stderr, "Invalid destination mac address: %s\n", argv[5]);
        exit(EXIT_FAILURE);
    }
    result.lan_mac = get_macaddr(result.lan_nic_name);
    result.wan_mac = get_macaddr(result.wan_nic_name);
    return result;
}
int open_pernic_rawsock(char* nic_name){
    int fd;
    struct ifreq ifr;
    
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        exit(EXIT_FAILURE);
    }
    strncpy(ifr.ifr_name, nic_name, IFNAMSIZ - 1);
    if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1) {
        fprintf(stderr, "ioctl SIOCGIFINDEX failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (fd < 0) {
        fprintf(stderr, "Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_ll addr;
    memset(&addr, 0x00, sizeof(addr));
    addr.sll_family = AF_PACKET;
    addr.sll_protocol = htons(ETH_P_ALL);
    addr.sll_ifindex = ifr.ifr_ifindex;
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        fprintf(stderr, "bind failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return fd;
}
Buffer do_seg6encap(arg config, Buffer* payload){
    Buffer tmpbuf;
    buffer_init(&tmpbuf);
    
    struct ether_header eth_hdr = {
        config.dst_mac.ether_addr_octet, // dst
        config.lan_mac.ether_addr_octet, // src
        htons(ETHERTYPE_IPV6) // ethertype
    };
    buffer_append(&tmpbuf,(uint8_t *)&eth_hdr, sizeof(eth_hdr));

    struct ip6_hdr ipv6_hdr= {
        .ip6_flow = htonl(0x60000000),
        .ip6_plen = htons(72),
        .ip6_nxt = IPPROTO_ROUTING,
        .ip6_hlim = 63,
        .ip6_src= config.ip6_srcaddr,
        .ip6_dst= config.ip6_dstaddr
    };
    buffer_append(&tmpbuf,(uint8_t *)&ipv6_hdr, sizeof(struct ip6_hdr));

    struct ipv6_sr_hdr *srh = malloc(sizeof(struct ipv6_sr_hdr) + sizeof(struct in6_addr));
    memset(srh, 0, sizeof(struct ipv6_sr_hdr) + sizeof(struct in6_addr));
    srh->nexthdr = 0x8f; // Ethernet!
    srh->hdrlen = 0x02;
    srh->type = 0x04;
    srh->segments_left = 0x00;
    srh->first_segment = 0x00;
    srh->flags = 0x00;
    srh->tag = 0x00;
    memcpy(&srh->segments[0], &config.ip6_dstaddr, sizeof(struct in6_addr));
    buffer_append(&tmpbuf,(uint8_t *)srh, sizeof(struct ipv6_sr_hdr) + sizeof(struct in6_addr));

    buffer_append(&tmpbuf, payload->v, payload->len);

    return tmpbuf;
}

int main(int argc, char *argv[]){
    arg config = parse_arg(argc, argv);
    int lan_fd = open_pernic_rawsock(config.lan_nic_name);
    int wan_fd = open_pernic_rawsock(config.wan_nic_name);

    struct sockaddr_ll dst_addr;
    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.sll_family = AF_PACKET;
    dst_addr.sll_protocol = htons(ETH_P_ALL);
    dst_addr.sll_ifindex = if_nametoindex(config.wan_nic_name);
    dst_addr.sll_halen = ETH_ALEN;
    memcpy(dst_addr.sll_addr, config.dst_mac.ether_addr_octet, ETH_ALEN);

    Buffer rcvbuf;
    buffer_init(&rcvbuf);
    Buffer sendbuf;
    while (1){
        ssize_t len = recv(lan_fd, rcvbuf.v, rcvbuf.len, 0);
        if (len < 0) {
            fprintf(stderr, "Failed to receive\n");
            return 1;
        }else if (len!=0){
            printf("payload: ");
            buffer_print(&rcvbuf);
            sendbuf = do_seg6encap(config, &rcvbuf);
            int err = sendto(wan_fd, sendbuf.v, sendbuf.len, 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));
            if (err < 0) {
                perror("sendto");
                close(wan_fd);
                exit(EXIT_FAILURE);
            }
            printf("SRv6 packet sent successfully.\n");
        }
    }
}
