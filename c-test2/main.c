#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <arpa/inet.h>

#define MAX_SEGMENTS 16

// Segment Routing Headerの構造体定義
struct segment_routing_header {
    uint8_t next_header;  // 次のヘッダーのタイプ (通常はIPv6の次のヘッダータイプ)
    uint8_t hdr_ext_len;  // ヘッダーエクステンションの長さ (8バイト単位)
    uint8_t routing_type; // セグメントルーティングの種類
    uint8_t segments_left; // 残りのセグメント数
    uint8_t last_entry;   // 最後のエントリーのインデックス
    uint8_t flags;        // フラグフィールド
    uint16_t tag;         // タグ (オプション)
    uint32_t reserved;    // 予約済みフィールド
    uint32_t segments[MAX_SEGMENTS]; // セグメント識別子のリスト
};



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
    char packet[1024];
    // 中身を0で初期化する
    memset(packet, 0, 1024);
    // ipv6ヘッダーの構造体のポインタ = packetの先頭アドレス (packetにipv6ヘッダーの構造体を被せる=キャストする)
    struct ip6_hdr *ip6_header = (struct ip6_hdr *) packet;
    // "->" : アロー演算子 (構造体の中身にアクセスする) 
    // htonl() : ホストバイトオーダーからネットワークバイトオーダーに32ビットの整数を変換する
    // htons() : ホストバイトオーダーからネットワークバイトオーダーに16ビットの整数を変換する
    // inet_pton() : ドット形式のIPv4アドレスまたはIPv6アドレスをバイナリ形式に変換する
    ip6_header->ip6_flow = htonl((6 << 28) | (0 << 20) | 0);
    ip6_header->ip6_plen = htons(1024 - sizeof(struct ip6_hdr));
    ip6_header->ip6_nxt = IPPROTO_ICMPV6;
    ip6_header->ip6_hops = 255;
    inet_pton(AF_INET6, "::1", &(ip6_header->ip6_src));
    inet_pton(AF_INET6, "::1", &(ip6_header->ip6_dst));

    // パケットのペイロード部分(packetに皮を被せる)
    char *payload = packet + sizeof(struct ip6_hdr);
    // strcpy() : 文字列をバイナリにして代入する
    strcpy(payload, "Hello, World!");

    // sockaddr_in6はソケットで使うアドレスなどを格納する
    // アドレス・ポート・フロー情報・スコープIDを格納できる
    struct sockaddr_in6 dest_addr;
    memset(&dest_addr, 0, sizeof(struct sockaddr_in6));
    dest_addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, "::1", &(dest_addr.sin6_addr));
    
    // sockfdにpacketを1024バイト
    if (sendto(sockfd, packet, 1024, 0, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr_in6)) < 0) {
        perror("Failed to send packet");
        exit(1);
    }

    printf("Packet sent successfully!\n");
    close(sockfd);
    return 0;
}