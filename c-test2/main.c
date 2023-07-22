#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>


int main(){
    const int on = 1;
    int sockfd = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("Failed to create socket");
        exit(1);
    }
    if (setsockopt(sockfd, IPPROTO_IPV6, IP_HDRINCL, &on, sizeof(on)) < 0) {
        perror("Failed to set socket options");
        exit(1);
    }

    char packet[1024];
    memset(packet, 0, 1024);
    struct ip6_hdr *ip6_header = (struct ip6_hdr *) packet;
    ip6_header->ip6_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip6_header->ip6_plen = htons(1024 - sizeof(struct ip6_hdr));
    ip6_header->ip6_nxt = IPPROTO_ICMPV6;
    ip6_header->ip6_hops = 255;
    inet_pton(AF_INET6, "::1", &(ip6_header->ip6_src));
    inet_pton(AF_INET6, "::1", &(ip6_header->ip6_dst));

    char *payload = packet + sizeof(struct ip6_hdr);
    strcpy(payload, "Hello, World!");
    struct sockaddr_in6 dest_addr;
    memset(&dest_addr, 0, sizeof(struct sockaddr_in6));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &(dest_addr.sin6_addr));
    
    if (sendto(sockfd, packet, 1024, 0, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr_in6)) < 0) {
        perror("Failed to send packet");
        exit(1);
    }
    printf("Packet sent successfully!\n");
    close(sockfd);
    return 0;
}