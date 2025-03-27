#include <linux/bpf.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <linux/ipv6.h>
#include <linux/seg6.h>

#define IFIDX_LAN 2
#define IFIDX_WAN 3

typedef uint8_t u8;
typedef uint16_t u16;

static inline int encap(struct xdp_md *ctx)
{
	u8 *data_end = (const u8 *)(long)ctx->data_end;
	u8 *data = (const u8 *)(long)ctx->data;
	const u16 plen = ((data_end-data) > 1500 ? 1500 : (data_end-data));

	if (data + sizeof(struct ethhdr) > data_end) {
		return XDP_ABORTED;
	}

	struct ethhdr ethh = {
		.h_dest = {0x66, 0xaa, 0x4b, 0xa6, 0xd6, 0xba},
		.h_source = {0x12, 0xa6, 0xe0, 0x4b, 0x94, 0x4a},
		.h_proto = htons(ETH_P_IPV6)
	};
	struct ipv6hdr ipv6h = {
		.version = 6,
		.flow_lbl = {0x00, 0x00, 0x00},
		.nexthdr = IPPROTO_ROUTING,
		.hop_limit = 63,
		.saddr = { .s6_addr = {
			0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }},
		.daddr = { .s6_addr = {
			0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }},
	};
	struct {
		struct ipv6_sr_hdr srh;
		struct in6_addr sid;
	} srh_alloc = {0};
	struct ipv6_sr_hdr *srh = &srh_alloc.srh;
	*srh = (struct ipv6_sr_hdr){
		.nexthdr = 0x8f, // 0x8f(143)=Eth ref: RFC8986 Sec4.9
		.type = 0x04, // SRH ref: RFC8754 Sec2	
		.hdrlen = 0x02,
		.segments_left = 0x00, 
		.first_segment = 0x00,
		.flags = 0x00,
		.tag = 0x00,
	};
	u8 sid[16] = { 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
	__builtin_memcpy(&srh->segments[0], &sid, sizeof(sid));
	ipv6h.payload_len = htons(plen+(u16)(sizeof srh_alloc));
	

	if (bpf_xdp_adjust_head(ctx,0
				- (int)sizeof(struct ethhdr)
				- (int)sizeof(struct ipv6hdr)
				- (int)sizeof(srh_alloc)
				)){ 
		return XDP_ABORTED; 
	}

	data_end = (const u8 *)(long)ctx->data_end;
	data = (const u8 *)(long)ctx->data;
	if ( data + (int)sizeof(struct ethhdr)
		+ (int)sizeof(struct ipv6hdr)
		+ (int)sizeof(srh_alloc)
		> data_end){
		return XDP_ABORTED;
	}


	u8 *hdr_p = data;
	__builtin_memcpy(hdr_p, &ethh, sizeof(ethh));
	hdr_p += sizeof(ethh);
	__builtin_memcpy(hdr_p, &ipv6h, sizeof(ipv6h));
	hdr_p += sizeof(ipv6h);
	__builtin_memcpy(hdr_p, &srh_alloc, sizeof(srh_alloc));
	
	int ifindex = ctx->ingress_ifindex;
	char msg[] = "ifidx: %d";
	bpf_trace_printk(msg, sizeof msg, ifindex);
	return 0;
}

SEC("xdp")
int xdp_brg(struct xdp_md *ctx)
{
	__u32 ifidx = ctx->ingress_ifindex;	
	if (ifidx == IFIDX_LAN) {
		if (encap(ctx)) return XDP_ABORTED;
		bpf_redirect(IFIDX_WAN, 0);
		return XDP_REDIRECT;
	}
	return XDP_PASS;	
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
