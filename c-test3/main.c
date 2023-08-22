#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>
#include <linux/seg6.h>



int main(){
    const int on = 1;
    // ソケットを開く
    int sockfd = socket(AF_INET6, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // オプションを設定する
    if (setsockopt(sockfd, IPPROTO_IPV6, IP_HDRINCL, &on, sizeof(on)) < 0) {
        perror("Failed to set socket options");
        exit(1);
    }

    // パケットの入れ物
    char buf[1024];
    // 中身を0で初期化する
    memset(buf, 0, 1024);
    
    // ipv6ヘッダーの構造体のポインタ = packetの先頭アドレス (packetにipv6ヘッダーの構造体を被せる=キャストする)
    struct ip6_hdr *ip6_header = (struct ip6_hdr *) buf;
    // "->" : アロー演算子 (構造体の中身にアクセスする) 
    // htonl() : ホストバイトオーダーからネットワークバイトオーダーに32ビットの整数を変換する
    // htons() : ホストバイトオーダーからネットワークバイトオーダーに16ビットの整数を変換する
    // inet_pton() : ドット形式のIPv4アドレスまたはIPv6アドレスをバイナリ形式に変換する
    ip6_header->ip6_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip6_header->ip6_nxt = IPPROTO_ROUTING;
    ip6_header->ip6_hops = 255;
    ip6_header->ip6_plen = htons(sizeof(struct ip6_hdr) + sizeof(struct ipv6_sr_hdr));
    inet_pton(AF_INET6, "::1", &(ip6_header->ip6_src));
    inet_pton(AF_INET6, "1::1", &(ip6_header->ip6_dst));
    // SRでは、Active Segmentがdest addrになる
    // inet_pton(AF_INET6, "::1", &(ip6_header->ip6_dst));
    //bufferにipv6ヘッダーを入れる
    memcpy(buf, ip6_header, sizeof(struct ip6_hdr));

    // srヘッダーの構造体のポインタ = packetの先頭アドレス + ipv6ヘッダーのサイズ (packetにsrヘッダーの構造体を被せる=キャストする)
    struct ipv6_sr_hdr *sr_header = (struct ipv6_sr_hdr *) (buf + sizeof(struct ip6_hdr));
    // "->" : アロー演算子 (構造体の中身にアクセスする)
    sr_header->nexthdr = IPPROTO_NONE;
    // SRHの場合は4
    sr_header->type = 4;
    // セグメントの何番目を使う？
    sr_header->segments_left = 0;
    // 
    // セグメントの最後の番号 (0から数える)
    sr_header->first_segment = 1;
    // 特殊用途だけど普通は0らしい
    sr_header->flags = 0;
    sr_header->tag = 114514;
    inet_pton(AF_INET6, "ffff:ffff:ffff:ffff", &(sr_header->segments[0]));
    // 型が違ってできない　ほんとうはこうやりたい
    // ip6_header->ip6_dst = sr_header->segments[0];
    uint8_t len = 8 + 16 * 1;
    sr_header->hdrlen = (len >> 3) -1;
    //bufferにsrヘッダーを入れる
    memcpy(buf + sizeof(struct ip6_hdr), sr_header, sizeof(struct ipv6_sr_hdr));
    


    // パケットのペイロード部分(packetに皮を被せる)
    // strcpy() : 文字列をバイナリにして代入する
    //strcpy(payload, "Hello, World!");
    //memcpy(buf + sizeof(struct ip6_hdr) + sizeof(struct segment_routing_header), "Hello, World!", 14);
    


    // sockaddr_in6はソケットで使うアドレスなどを格納する
    // アドレス・ポート・フロー情報・スコープIDを格納できる
    struct sockaddr_in6 dest_addr;
    memset(&dest_addr, 0, sizeof(struct sockaddr_in6));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &(dest_addr.sin6_addr));
    
    // sockfdにpacketをバイト
    if (sendto(sockfd, buf, sizeof(struct ip6_hdr) + sizeof(struct ipv6_sr_hdr), 0, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr_in6)) < 0) {
        perror("Failed to send packet");
        exit(1);
    }

    printf("Packet sent successfully!\n");
    close(sockfd);
    return 0;
}