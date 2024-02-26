#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <netinet/icmp6.h>

#define PACKET_SIZE 1024

int main() {
    // Create a RAW socket
    int sockfd = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("Failed to create socket");
        return 1;
    }

    // Set socket options to allow IP header inclusion
    int on = 1;
    if (setsockopt(sockfd, IPPROTO_IPV6, IP_HDRINCL, &on, sizeof(on)) < 0) {
        perror("Failed to set socket options");
        return 1;
    }

    // Create an IPv6 packet
    char packet[PACKET_SIZE];
    memset(packet, 0, PACKET_SIZE);

    // Set the IPv6 header
    struct ip6_hdr *ip6_header = (struct ip6_hdr *) packet;
    ip6_header->ip6_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip6_header->ip6_plen = htons(PACKET_SIZE - sizeof(struct ip6_hdr));
    ip6_header->ip6_nxt = IPPROTO_ICMPV6;
    ip6_header->ip6_hops = 255;
    inet_pton(AF_INET6, "2001:db8::1", &(ip6_header->ip6_src));
    inet_pton(AF_INET6, "2001:db8::2", &(ip6_header->ip6_dst));

    // Set the ICMPv6 payload
    char *payload = packet + sizeof(struct ip6_hdr);
    strcpy(payload, "Hello, World!");

    // Send the packet
    struct sockaddr_in6 dest_addr;
    memset(&dest_addr, 0, sizeof(struct sockaddr_in6));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "2001:db8::2", &(dest_addr.sin6_addr));

    if (sendto(sockfd, packet, PACKET_SIZE, 0, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr_in6)) < 0) {
        perror("Failed to send packet");
        return 1;
    }

    printf("Packet sent successfully!\n");

    // Close the socket
    close(sockfd);

    return 0;
}
