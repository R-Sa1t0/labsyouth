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

#include "lib/buf.h"
#include "lib/util.h"

// sudo ip netns exec IN1 ./a.out fc00:1::2 fc00:12::1 IN1-IC1 IN1-IR1 fe:6a:96:11:e7:1c
// sudo ip netns exec IN2 ./a.out fc00:2::2 fc00:11::1 IN2-IC2 IN2-IR1 5e:93:21:63:f5:cd

typedef struct {
    struct in6_addr ip6_srcaddr;
    struct in6_addr ip6_dstaddr;
    char *lan_nic_name;
    char *wan_nic_name;
    struct ether_addr lan_mac;
    struct ether_addr wan_mac;
    struct ether_addr dst_mac;
}arg;
int parse_arg(arg *result, const int argc, const char *argv[]){
    if (argc != 6) {
        fprintf(stderr, "Usage: %s [srcaddr] [dstaddr] [lan-side-nic-name] [wan-side-nic-name] [dst mac addr]\n", argv[0]);
        return -1;
    }
    if (inet_pton(AF_INET6, argv[1], &result->ip6_srcaddr) != 1) {
        fprintf(stderr, "Invalid source IPv6 address: %s\n", argv[1]);
        return -2;
    }
    if (inet_pton(AF_INET6, argv[2], &result->ip6_dstaddr) != 1) {
        fprintf(stderr, "Invalid destination IPv6 address: %s\n", argv[2]);
        return -3;
    }
    result->lan_nic_name = strdup(argv[3]);
    if (result->lan_nic_name == NULL) {
        perror("strdup");
        return -4;
    }
    result->wan_nic_name = strdup(argv[4]);
    if (result->wan_nic_name == NULL) {
        perror("strdup");
        return -5;
    }
    if ((parse_macaddr(&result->dst_mac, argv[5]))!=0) {
        fprintf(stderr, "Invalid destination mac address: %s\n", argv[5]);
        return -6;
    }
    if ((get_lladdr(&result->lan_mac, result->lan_nic_name))!=0) return -1;
    if ((get_lladdr(&result->wan_mac, result->wan_nic_name))!=0) return -1;
    return 0;
}

// TODO : 返り値はエラー、結果格納用のポインタを渡すようにする
Buffer do_seg6encap(arg config, const Buffer* payload){
    Buffer tmpbuf;
    buffer_init(&tmpbuf);
    
    struct ether_header eth_hdr = {
        .ether_type = htons(ETHERTYPE_IPV6) // ethertype
    };
    memcpy(eth_hdr.ether_dhost, config.dst_mac.ether_addr_octet, sizeof(eth_hdr.ether_dhost));
    memcpy(eth_hdr.ether_shost, config.lan_mac.ether_addr_octet, sizeof(eth_hdr.ether_shost));

    buffer_append(&tmpbuf,(uint8_t *)&eth_hdr, sizeof(eth_hdr));

    struct ip6_hdr ipv6_hdr= {
        .ip6_flow = htonl(0x60000000),
        //.ip6_plen = htons(72),
        .ip6_plen = htons(payload->len+24), //payload len + SRH(1sid)len
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
    arg config;
    if ((parse_arg(&config, argc, (const char **)argv))<0) exit(1);
    int lan_fd, wan_fd; //open_pernic_rawsock(config.lan_nic_name);
    if ((open_rawsock_pernic(&lan_fd, config.lan_nic_name))<0) exit(EXIT_FAILURE);
    if ((open_rawsock_pernic(&wan_fd, config.wan_nic_name))<0) exit(EXIT_FAILURE);
    for (size_t i = 0; i < 6; i++) printf("%02x", config.dst_mac.ether_addr_octet[i]);
    for (size_t i = 0; i < 6; i++) printf("%02x", config.wan_mac.ether_addr_octet[i]);


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
    fprintf(stdout ,"buffer ok!\n");
    
    while (1){
        fprintf(stdout ,"while 1\n");

        ssize_t len = recv(lan_fd, rcvbuf.v, sizeof rcvbuf.v, 0);

        fprintf(stdout ,"recv\n");
        printf("len : %d\n", len);

        if (len < 0) {
            fprintf(stderr, "Failed to receive\n");
            return 1;
        }else if (len!=0){
            printf("payload: \n");
            buffer_print(&rcvbuf);

            rcvbuf.len = len;
            sendbuf = do_seg6encap(config, &rcvbuf);
            
            printf("encaped packet: \n");
            buffer_print(&sendbuf);

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
