#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/icmp6.h>
#include <netinet/ip6.h>
#include <netinet/ether.h>
#include <linux/if_packet.h>
//#include <netpacket/packet.h>
//#include <net/ethernet.h>
#include <net/if.h>

int add_bytestobuf(int offset, int len, char *buf, char *data) {
    for (int i = 0; i < len; i++) {
        buf[offset + i] = data[i];
    }
    return offset + len;
}

int main() {
    // Create a raw socket
    int sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    char pbuf[126];
    memset(pbuf, 0, sizeof(pbuf));

    // L2 (Ethernet) header
    // dst addr (5e:93:21:63:f5:cd)
    char eth_dst_mac[] = {0x5e, 0x93, 0x21, 0x63, 0xf5, 0xcd};
    add_bytestobuf(0, 6, pbuf, eth_dst_mac);
    // src addr (52:b3:7d:78:93:61)
    char eth_src_mac[] = {0x52, 0xb3, 0x7d, 0x78, 0x93, 0x61};
    add_bytestobuf(6, 6, pbuf, eth_src_mac);
    // ethertype (IPv6)
    char ethertype[] = {0x86, 0xdd};
    add_bytestobuf(12, 2, pbuf, ethertype);

    // L3 (IPv6) header
    // version, traffic class, flow label
    char vtcfl[] = {0x60, 0x00, 0x00, 0x00};
    add_bytestobuf(14, 4, pbuf, vtcfl);
    // payload length (78)
    char payload_len[] = {0x00, 0x48};
    add_bytestobuf(18, 2, pbuf, payload_len);
    // next header (SRv6: 43)
    char next_hdr[] = {0x2b};
    add_bytestobuf(20, 1, pbuf, next_hdr);
    // hop limit (64)
    char hop_limit[] = {0x3f};
    add_bytestobuf(21, 1, pbuf, hop_limit);
    // src addr (fc00:2::2 / fc00:2:0:0:0:0:0:2)
    char ip_src_addr[] = {0xfc, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
    add_bytestobuf(22, 16, pbuf, ip_src_addr);
    // dst addr (fc00:11::1 / fc00:11:0:0:0:0:0:1)
    char ip_dst_addr[] = {0xfc, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    add_bytestobuf(38, 16, pbuf, ip_dst_addr);
    // SRH
    // next header (Ethernet: 143)
    char srh_next_hdr[] = {0x8f};
    add_bytestobuf(54, 1, pbuf, srh_next_hdr);
    // hdr ext len (2)
    char srh_hdr_ext_len[] = {0x02};
    add_bytestobuf(55, 1, pbuf, srh_hdr_ext_len);
    // routing type (Segment Routing: 4)
    char srh_routing_type[] = {0x04};
    add_bytestobuf(56, 1, pbuf, srh_routing_type);
    // Segment left (0)
    char srh_seg_left[] = {0x00};
    add_bytestobuf(57, 1, pbuf, srh_seg_left);
    // last entry (0)
    char srh_last_entry[] = {0x00};
    add_bytestobuf(58, 1, pbuf, srh_last_entry);
    // flags (0)
    char srh_flags[] = {0x00};
    add_bytestobuf(69, 1, pbuf, srh_flags);
    // first segment (0)
    char srh_first_seg[] = {0x00};
    add_bytestobuf(60, 1, pbuf, srh_first_seg);
    // tag (0)
    char srh_tag[] = {0x00, 0x00};
    add_bytestobuf(61, 2, pbuf, srh_tag);
    // segment list = ip_dst_addr
    char seg6_sid[] = {0xfc, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    // なぜかadd_bytestobuf(63, 16, pbuf, seg6_sid);だとだめ
    add_bytestobuf(62, 16, pbuf, seg6_sid);

    // Overlay L2 Header
    // dst addr (52:54:00:11:11:11)
    char overlay_eth_dst_mac[] = {0x52, 0x54, 0x00, 0x11, 0x11, 0x11};
    add_bytestobuf(78, 6, pbuf, overlay_eth_dst_mac);
    // src addr (52:54:00:22:22:22)
    char overlay_eth_src_mac[] = {0x52, 0x54, 0x00, 0x22, 0x22, 0x22};
    add_bytestobuf(84, 6, pbuf, overlay_eth_src_mac);
    // ethertype (IP)
    char overlay_ethertype[] = {0x08, 0x00};
    add_bytestobuf(90, 2, pbuf, overlay_ethertype);

    // Overlay L3 Header (IPv4)
    // version, IHL, DSCP, ECN
    char overlay_vihl[] = {0x45};
    add_bytestobuf(92, 1, pbuf, overlay_vihl);
    // total length (40)
    char overlay_total_len[] = {0x00, 0x22};
    add_bytestobuf(94, 2, pbuf, overlay_total_len);
    // indentification (1)
    char overlay_identification[] = {0xbc, 0x5e};
    add_bytestobuf(96, 2, pbuf, overlay_identification);
    // flags, fragment offset (0)
    char overlay_flags_fo[] = {0x40, 0x00};
    add_bytestobuf(98, 2, pbuf, overlay_flags_fo);
    // TTL (64)
    char overlay_ttl[] = {0x40};
    add_bytestobuf(100, 1, pbuf, overlay_ttl);
    // protocol (UDP=17)
    char overlay_protocol[] = {0x11};
    add_bytestobuf(101, 1, pbuf, overlay_protocol);
    // checksum (0)
    char overlay_checksum[] = {0x68, 0x6a};
    add_bytestobuf(102, 2, pbuf, overlay_checksum);
    // src addr (10.0.1.2)
    char overlay_ip_src_addr[] = {0x0a, 0x00, 0x01, 0x02};
    add_bytestobuf(104, 4, pbuf, overlay_ip_src_addr);
    // dst addr (10.0.1.1)
    char overlay_ip_dst_addr[] = {0x0a, 0x00, 0x01, 0x01};
    add_bytestobuf(108, 4, pbuf, overlay_ip_dst_addr);

    // UDP Header
    // src port (8080)
    char udp_src_port[] = {0x1f, 0x90};
    add_bytestobuf(112, 2, pbuf, udp_src_port);
    // dst port (46550)
    char udp_dst_port[] = {0xe5, 0xc8};
    add_bytestobuf(114, 2, pbuf, udp_dst_port);
    // length (14)
    char udp_len[] = {0x00, 0x0e};
    add_bytestobuf(116, 2, pbuf, udp_len);
    // checksum (0)
    char udp_checksum[] = {0x00, 0x00};
    add_bytestobuf(118, 2, pbuf, udp_checksum);
    // payload (わざとtypo)
    char payload[] = {0x48, 0x41, 0x4c, 0x4c, 0x4f, 0x0a};
    add_bytestobuf(120, 6, pbuf, payload);


    // dst addr : 52:b3:7d:78:93:61
    struct sockaddr_ll dest_addr;
    char ifname[] = "N2-R1";
    unsigned char mac_dest[6] = {0x52, 0xb3, 0x7d, 0x78, 0x93, 0x61};

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sll_family = AF_PACKET;
    dest_addr.sll_protocol = htons(ETH_P_ALL);
    dest_addr.sll_ifindex = if_nametoindex(ifname);
    dest_addr.sll_halen = ETH_ALEN;
    memcpy(dest_addr.sll_addr, mac_dest, ETH_ALEN);
    
    int err = sendto(sockfd, pbuf, sizeof(pbuf), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    if (err < 0) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("IPv6 packet sent successfully.\n");

    close(sockfd);
    return 0;
}
