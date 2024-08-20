#include <stdio.h>  // fprintf()
#include <stdlib.h> // exit(), EXIT_FAILURE
#include <stdint.h> // uint8_t
#include <string.h> // memset(), memcpy()
#include <unistd.h> // close()
#include <sys/socket.h> // socket(), size_t
#include <arpa/inet.h> // IPPROTO_RAW, htons
#include <netinet/ether.h> // ETH_ALEN, ETH_P_ALL
#include <linux/if_packet.h> // sockaddr_ll
#include <net/if.h> // if_nametoindex()

#include <net/ethernet.h>  //ethernet
#include <netinet/ip6.h> // ipv6 hdr
#include <linux/in6.h> // IPPROTO_ROUTING, IPPROTO_ETHERNET
#include <linux/seg6.h> // srv6 hdr
#include <netinet/ip.h>  // ipv4 hdr
#include <netinet/udp.h> // udp hdr 


// charは最大値が127までしか保証されてないので，uint8_tを使う
#define BUFFER_SIZE 1500

typedef struct{
    uint8_t v[BUFFER_SIZE];
    size_t len;
}Buffer;
void buffer_init(Buffer *buf){
    memset(buf->v, 0, BUFFER_SIZE);
    buf->len=0;
}
// size_t : 符号なし整数
void buffer_append(Buffer *buf, const uint8_t *data, size_t data_size){
    if (buf->len+data_size>BUFFER_SIZE){
        fprintf(stderr, "BUF_ERR: buffer full\n");
        exit(1);
    }
    memcpy(buf->v+buf->len, data, data_size);
    // or: memcpy(&buf->v[buf->len], data, data_size);
    buf->len+=data_size;
}
void buffer_print(Buffer *buf){
    for (int i=0; i<buf->len; i++) printf("%02x ", ((uint8_t *)buf->v)[i]);
    puts("");
}

int main() {
    Buffer pbuf1;
    buffer_init(&pbuf1);

    struct ether_header eth_hdr = {
        {0x5e, 0x93, 0x21, 0x63, 0xf5, 0xcd}, // dst
        {0x52, 0xb3, 0x7d, 0x78, 0x93, 0x61}, // src
        htons(ETHERTYPE_IPV6) // ethertype
    };
    buffer_append(&pbuf1,(uint8_t *)&eth_hdr, sizeof(eth_hdr));

    // L3 (IPv6) header
    struct in6_addr ip6_src_addr;
    inet_pton(AF_INET6, "fc00:2::2", &ip6_src_addr);
    //for (int i=0; i<sizeof(ip6_src_addr); i++) printf("%02x ", ((uint8_t *)&ip6_src_addr)[i]);
    struct in6_addr ip6_dst_addr;
    inet_pton(AF_INET6, "fc00:11::1", &ip6_dst_addr);
    //for (int i=0; i<sizeof(ip6_dst_addr); i++) printf("%02x ", ((uint8_t *)&ip6_dst_addr)[i]);
    struct ip6_hdr ipv6_hdr= {
        .ip6_flow = htonl(0x60000000),
        .ip6_plen = htons(72),
        .ip6_nxt = IPPROTO_ROUTING,
        .ip6_hlim = 63,
        .ip6_src= ip6_src_addr,
        .ip6_dst= ip6_dst_addr
    };
    buffer_append(&pbuf1,(uint8_t *)&ipv6_hdr, sizeof(struct ip6_hdr));
    

    // SRH
    struct ipv6_sr_hdr *srh = malloc(sizeof(struct ipv6_sr_hdr) + sizeof(struct in6_addr));
    memset(srh, 0, sizeof(struct ipv6_sr_hdr) + sizeof(struct in6_addr));
    srh->nexthdr = 0x8f;
    srh->hdrlen = 0x02;
    srh->type = 0x04;
    srh->segments_left = 0x00;
    srh->first_segment = 0x00;
    srh->flags = 0x00;
    srh->tag = 0x00;
    memcpy(&srh->segments[0], &ip6_dst_addr, sizeof(struct in6_addr));
    //for (int i=0; i<(sizeof(struct ipv6_sr_hdr) + sizeof(struct in6_addr)); i++) printf("%02x ", ((uint8_t *)srh)[i]); puts("");
    buffer_append(&pbuf1,(uint8_t *)srh, sizeof(struct ipv6_sr_hdr) + sizeof(struct in6_addr));

    // Overlay L2 Header
    struct ether_header overlay_eth_hdr = {
        {0x52, 0x54, 0x00, 0x11, 0x11, 0x11}, // dst
        {0x52, 0x54, 0x00, 0x22, 0x22, 0x22}, // src
        htons(ETHERTYPE_IP) // ethertype
    };
    buffer_append(&pbuf1,(uint8_t *)&overlay_eth_hdr, sizeof(overlay_eth_hdr));
    

    // Overlay L3 Header (IPv4)
    struct iphdr overlay_iphdr = {
        .version = 4, // IPv4
        .ihl = 5, // IP Header Length = 5 * 32bit words
        .tos = 0, 
        .tot_len = htons(34),
        .id = htons(0xbc5e),
        .frag_off = htons(0x4000), 
        .ttl = 64,
        .protocol = 0x11, // udp: 17
        .check = htons(0x686a), // checksum
        .saddr = htonl(0x0a000102), // src ip
        .daddr = htonl(0x0a000101) // dst ip
    };
    buffer_append(&pbuf1,(uint8_t *)&overlay_iphdr, sizeof(overlay_iphdr));

    // UDP Header
    uint8_t payload[] = {0x48, 0x41, 0x4c, 0x4c, 0x4f, 0x0a};
    struct udphdr overlay_udphdr = {
        .uh_sport = htons(8080),
        .uh_dport = htons(58824),
        .uh_ulen = htons(14),
        .uh_sum = 0
    };
    buffer_append(&pbuf1,(uint8_t *)&overlay_udphdr, sizeof(overlay_udphdr));
    buffer_append(&pbuf1, payload, sizeof payload);
    buffer_print(&pbuf1);


    // Create a raw socket
    int sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // dst addr : 52:b3:7d:78:93:61
    struct sockaddr_ll dst_addr;
    char ifname[] = "N2-R1";
    uint8_t mac_dest[6] = {0x52, 0xb3, 0x7d, 0x78, 0x93, 0x61};

    memset(&dst_addr, 0, sizeof(dst_addr));
    dst_addr.sll_family = AF_PACKET;
    dst_addr.sll_protocol = htons(ETH_P_ALL);
    dst_addr.sll_ifindex = if_nametoindex(ifname);
    dst_addr.sll_halen = ETH_ALEN;
    memcpy(dst_addr.sll_addr, mac_dest, ETH_ALEN);
    
    int err = sendto(sockfd, pbuf1.v, pbuf1.len, 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));

    if (err < 0) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("SRv6 packet sent successfully.\n");

    close(sockfd);
    return 0;
}
