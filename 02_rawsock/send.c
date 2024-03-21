#include <stdio.h>  // fprintf()
#include <stdlib.h> // exit(), EXIT_FAILURE
#include <stdint.h> // uint8_t
#include <string.h> // memset(), memcpy()
#include <unistd.h> // close()
#include <sys/socket.h> // socket(), size_t
#include <arpa/inet.h> // IPPROTO_RAW
#include <netinet/ether.h> // ETH_ALEN, ETH_P_ALL
#include <linux/if_packet.h> // sockaddr_ll
#include <net/if.h> // if_nametoindex()

//#include <net/ethernet.h>

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

int main() {
    // Create a raw socket
    int sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    Buffer pbuf;
    //uint8_t pbuf[126];
    buffer_init(&pbuf);

    // L2 (Ethernet) header
    // dst addr (5e:93:21:63:f5:cd)
    uint8_t eth_dst_mac[] = {0x5e, 0x93, 0x21, 0x63, 0xf5, 0xcd};
    buffer_append(&pbuf, eth_dst_mac, sizeof eth_dst_mac);
    // src addr (52:b3:7d:78:93:61)
    uint8_t eth_src_mac[] = {0x52, 0xb3, 0x7d, 0x78, 0x93, 0x61};
    buffer_append(&pbuf, eth_src_mac, sizeof eth_src_mac);
    // ethertype (IPv6)
    uint8_t ethertype[] = {0x86, 0xdd};
    buffer_append(&pbuf, ethertype, sizeof ethertype);

    // L3 (IPv6) header
    // version, traffic class, flow label
    uint8_t vtcfl[] = {0x60, 0x00, 0x00, 0x00};
    buffer_append(&pbuf, vtcfl, sizeof vtcfl);
    // payload length (78)
    uint8_t payload_len[] = {0x00, 0x48};
    buffer_append(&pbuf, payload_len, sizeof payload_len);
    // next header (SRv6: 43)
    uint8_t next_hdr[] = {0x2b};
    buffer_append(&pbuf, next_hdr, sizeof next_hdr);
    // hop limit (64)
    uint8_t hop_limit[] = {0x3f};
    buffer_append(&pbuf, hop_limit, sizeof hop_limit);
    // src addr (fc00:2::2 / fc00:2:0:0:0:0:0:2)
    uint8_t ip_src_addr[] = {0xfc, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
    buffer_append(&pbuf, ip_src_addr, sizeof ip_src_addr);
    // dst addr (fc00:11::1 / fc00:11:0:0:0:0:0:1)
    uint8_t ip_dst_addr[] = {0xfc, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    buffer_append(&pbuf, ip_dst_addr, sizeof ip_dst_addr);
    // SRH
    // next header (Ethernet: 143)
    uint8_t srh_next_hdr[] = {0x8f};
    buffer_append(&pbuf, srh_next_hdr, sizeof srh_next_hdr);
    // hdr ext len (2)
    uint8_t srh_hdr_ext_len[] = {0x02};
    buffer_append(&pbuf, srh_hdr_ext_len, sizeof srh_hdr_ext_len);
    // routing type (Segment Routing: 4)
    uint8_t srh_routing_type[] = {0x04};
    buffer_append(&pbuf, srh_routing_type, sizeof srh_routing_type);
    // Segment left (0)
    uint8_t srh_seg_left[] = {0x00};
    buffer_append(&pbuf, srh_seg_left, sizeof srh_seg_left);
    // last entry (0)
    uint8_t srh_last_entry[] = {0x00};
    buffer_append(&pbuf, srh_last_entry, sizeof srh_last_entry);
    // flags (0)
    uint8_t srh_flags[] = {0x00};
    buffer_append(&pbuf, srh_flags, sizeof srh_flags);
    // tag (0)
    uint8_t srh_tag[] = {0x00, 0x00};
    buffer_append(&pbuf, srh_tag, sizeof srh_tag);
    // segment list = ip_dst_addr
    uint8_t seg6_sid[] = {0xfc, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x00,
                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
    // なぜかadd_bytestobuf(63, 16, pbuf, seg6_sid);だとだめ
    buffer_append(&pbuf, seg6_sid, sizeof seg6_sid);

    // Overlay L2 Header
    // dst addr (52:54:00:11:11:11)
    uint8_t overlay_eth_dst_mac[] = {0x52, 0x54, 0x00, 0x11, 0x11, 0x11};
    buffer_append(&pbuf, overlay_eth_dst_mac, sizeof overlay_eth_dst_mac);
    // src addr (52:54:00:22:22:22)
    uint8_t overlay_eth_src_mac[] = {0x52, 0x54, 0x00, 0x22, 0x22, 0x22};
    buffer_append(&pbuf, overlay_eth_src_mac, sizeof overlay_eth_src_mac);
    // ethertype (IP)
    uint8_t overlay_ethertype[] = {0x08, 0x00};
    buffer_append(&pbuf, overlay_ethertype, sizeof overlay_ethertype);

    // Overlay L3 Header (IPv4)
    // version, IHL, DSCP, ECN
    uint8_t overlay_vihl[] = {0x45, 0x00};
    buffer_append(&pbuf, overlay_vihl, sizeof overlay_vihl);
    // total length (40)
    uint8_t overlay_total_len[] = {0x00, 0x22};
    buffer_append(&pbuf, overlay_total_len, sizeof overlay_total_len);
    // indentification (1)
    uint8_t overlay_identification[] = {0xbc, 0x5e};
    buffer_append(&pbuf, overlay_identification, sizeof overlay_identification);
    // flags, fragment offset (0)
    uint8_t overlay_flags_fo[] = {0x40, 0x00};
    buffer_append(&pbuf, overlay_flags_fo, sizeof overlay_flags_fo);
    // TTL (64)
    uint8_t overlay_ttl[] = {0x40};
    buffer_append(&pbuf, overlay_ttl, sizeof overlay_ttl);
    // protocol (UDP=17)
    uint8_t overlay_protocol[] = {0x11};
    buffer_append(&pbuf, overlay_protocol, sizeof overlay_protocol);
    // checksum (0)
    uint8_t overlay_checksum[] = {0x68, 0x6a};
    buffer_append(&pbuf, overlay_checksum, sizeof overlay_checksum);
    // src addr (10.0.1.2)
    uint8_t overlay_ip_src_addr[] = {0x0a, 0x00, 0x01, 0x02};
    buffer_append(&pbuf, overlay_ip_src_addr, sizeof overlay_ip_src_addr);
    // dst addr (10.0.1.1)
    uint8_t overlay_ip_dst_addr[] = {0x0a, 0x00, 0x01, 0x01};
    buffer_append(&pbuf, overlay_ip_dst_addr, sizeof overlay_ip_dst_addr);

    // UDP Header
    // src port (8080)
    uint8_t udp_src_port[] = {0x1f, 0x90};
    buffer_append(&pbuf, udp_src_port, sizeof udp_src_port);
    // dst port (46550)
    uint8_t udp_dst_port[] = {0xe5, 0xc8};
    buffer_append(&pbuf, udp_dst_port, sizeof udp_dst_port);
    // length (14)
    uint8_t udp_len[] = {0x00, 0x0e};
    buffer_append(&pbuf, udp_len, sizeof udp_len);
    // checksum (0)
    uint8_t udp_checksum[] = {0x00, 0x00};
    buffer_append(&pbuf, udp_checksum, sizeof udp_checksum);
    // payload (わざとtypo)
    uint8_t payload[] = {0x48, 0x41, 0x4c, 0x4c, 0x4f, 0x0a};
    buffer_append(&pbuf, payload, sizeof payload);


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
    
    int err = sendto(sockfd, pbuf.v, pbuf.len, 0, (struct sockaddr *)&dst_addr, sizeof(dst_addr));

    if (err < 0) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("SRv6 packet sent successfully.\n");

    close(sockfd);
    return 0;
}
