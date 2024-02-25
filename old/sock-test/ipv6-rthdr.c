#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <linux/seg6.h>

int main(){
    int sockfd = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    struct sockaddr_in6 dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &(dest_addr.sin6_addr));

    struct ip6_hdr ip6hdr;
    memset(&ip6hdr, 0, sizeof(ip6hdr));
    ip6hdr.ip6_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip6hdr.ip6_nxt = IPPROTO_ROUTING;
    ip6hdr.ip6_hops = 255;

    //struct ipv6_sr_hdr srhdr;
    //memset(&srhdr, 0, sizeof(srhdr));
    //srhdr.nexthdr = IPPROTO_NONE;



    // sockoptにipv6-rthdrを指定
    //setsockopt(sockfd, IPPROTO_IPV6, IPV6_RTHDR, &rthdr, sizeof(rthdr));

}