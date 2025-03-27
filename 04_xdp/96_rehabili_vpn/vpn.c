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
typedef uint32_t u32;

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 1);
	__type(key, __u8);
	__type(value, struct cfg);
} vpn_cfg_map SEC(".maps");

struct cfg {
	u32 ifidx_wan;
	u32 ifidx_lan;
	u8 smac[6];
	u8 dmac[6];
	u8 saddr[16];
	u8 daddr[16];
	u8 sid[16];
};

static inline int encap(struct xdp_md *ctx, struct cfg *vcfg)
{
	u8 *data_end = (const u8 *)(long)ctx->data_end;
	u8 *data = (const u8 *)(long)ctx->data;
	const u16 plen = ((data_end-data) > 1500 ? 1500 : (data_end-data));


	struct ethhdr ethh = {
		.h_proto = htons(ETH_P_IPV6)
	};
	__builtin_memcpy(ethh.h_dest, vcfg->dmac, ETH_ALEN);
	__builtin_memcpy(ethh.h_source, vcfg->smac, ETH_ALEN);

	struct ipv6hdr ipv6h = {
		.version = 6,
		.flow_lbl = {0x00, 0x00, 0x00},
		.nexthdr = IPPROTO_ROUTING,
		.hop_limit = 63,
	};
	__builtin_memcpy(&ipv6h.saddr, vcfg->saddr, 16);
	__builtin_memcpy(&ipv6h.daddr, vcfg->daddr, 16);

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
	__builtin_memcpy(&srh->segments[0], &vcfg->sid, 16);
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
	
	bpf_redirect(vcfg->ifidx_wan, 0);
	return XDP_REDIRECT;
}

SEC("xdp")
int xdp_vpn(struct xdp_md *ctx)
{

	u8 key = 0;
	struct cfg *vcfg = bpf_map_lookup_elem(&vpn_cfg_map, &key);
	if (!vcfg) return XDP_ABORTED;
	
	__u32 ifidx = ctx->ingress_ifindex;	
	if (ifidx == vcfg->ifidx_lan) {
		return encap(ctx, vcfg);
	}
	return XDP_PASS;	
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
