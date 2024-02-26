#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#include <arpa/inet.h>

#define PAYLOAD_SIZE 64

int main() {
    int sockfd;
    struct sockaddr_in6 dest_addr;
    struct ip6_hdr ip_header;
    char payload[PAYLOAD_SIZE] = "This is my custom payload!";

    // Create a raw socket
    sockfd = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Set the destination address
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &(dest_addr.sin6_addr));

    // Set the IPv6 header fields
    memset(&ip_header, 0, sizeof(ip_header));
    ip_header.ip6_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip_header.ip6_plen = htons(PAYLOAD_SIZE);
    ip_header.ip6_nxt = 59;  // Replace with the desired protocol
    ip_header.ip6_hops = 255;
    inet_pton(AF_INET6, "::1", &(ip_header.ip6_src));
    inet_pton(AF_INET6, "::1", &(ip_header.ip6_dst));

    // Send the packet
    if (sendto(sockfd, &ip_header, sizeof(ip_header), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) < 0) {
        perror("sendto");
        exit(1);
    }

    // Close the socket
    close(sockfd);

    return 0;
}
