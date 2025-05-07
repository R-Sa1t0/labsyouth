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
typedef uint64_t u64;

struct {
	__uint(type, BPF_MAP_TYPE_HASH);
	__uint(max_entries, 1);
	__type(key, u8);
	__type(value, struct cfg);
} seg6vpn_cfg_map SEC(".maps");

struct cfg {
	u32 ifidx_wan;
	u32 ifidx_lan;
	u8 e_smac[6];
	u8 e_dmac[6];
	u8 e_saddr[16];
	u8 e_daddr[16];
	u8 e_sid[16];
	u8 d_sid[16];
};

static inline void dbg(const struct xdp_md *ctx) {
	bpf_printk("ingress_ifidx: %lu\n", ctx->ingress_ifindex);
}

static inline void hex_dump(const char *name, const void *_head, size_t len) {
	bpf_printk("%s = ", name);

	const u8 *head = (const u8 *)_head;
	for (size_t i=0; i<len; i++) {
		bpf_trace_printk("%02x ",sizeof("%02x "), head[i]);
	}
}

static inline void in6addr_dump(const char *name, const void *in6addr){
	bpf_printk("%s = %pI6\n", name, in6addr);
}


static inline int encap(struct xdp_md *ctx, struct cfg *vcfg)
{
	u8 *data_end = (u8 *)(long)ctx->data_end;
	u8 *data = (u8 *)(long)ctx->data;
	const u16 plen = ((data_end)-data) > 1500 ? 1500 : (data_end-data);

	struct ethhdr ethh = {
		.h_proto = bpf_htons(ETH_P_IPV6)
	};
	__builtin_memcpy(ethh.h_dest, vcfg->e_dmac, ETH_ALEN);
	__builtin_memcpy(ethh.h_source, vcfg->e_smac, ETH_ALEN);

	struct ipv6hdr ipv6h = {
		.version = 6,
		.flow_lbl = {0x00, 0x00, 0x00},
		.nexthdr = IPPROTO_ROUTING,
		.hop_limit = 63,
	};
	__builtin_memcpy(&ipv6h.saddr, vcfg->e_saddr, 16);
	__builtin_memcpy(&ipv6h.daddr, vcfg->e_daddr, 16);
	in6addr_dump("encap: dst addr ", vcfg->e_daddr);
	in6addr_dump("encap: srv6 sid", vcfg->e_sid);

	_Alignas(16) char srh_alloc [sizeof(struct ipv6_sr_hdr) + sizeof (struct in6_addr)];	
	struct ipv6_sr_hdr *srh = (struct ipv6_sr_hdr*)srh_alloc;
	*srh = (struct ipv6_sr_hdr){
		.nexthdr = 0x8f, // 0x8f(143)=Eth ref: RFC8986 Sec4.9
		.hdrlen = 0x02,
		.type = 0x04,
		.segments_left = 0x00,
		.first_segment = 0x00,
		.flags = 0x00,
		.tag = 0x00,
	};
	__builtin_memcpy(&srh->segments[0], &vcfg->e_sid, 16);
	ipv6h.payload_len = bpf_htons(plen+(u16)(sizeof srh_alloc));

	if (bpf_xdp_adjust_head(ctx,0
			- (int)sizeof(struct ethhdr)
			- (int)sizeof(struct ipv6hdr)
			- (int)sizeof(srh_alloc)
			)){
		return XDP_PASS;
	}
	data_end = (u8 *)(long)ctx->data_end;
	data = (u8 *)(long)ctx->data;
	if ( data + (int)sizeof(struct ethhdr)
			+ (int)sizeof(struct ipv6hdr)
			+ (int)sizeof(srh_alloc)
			> data_end){
		return XDP_PASS;
	}

	u8 *hdr_p = data;
	__builtin_memcpy(hdr_p, &ethh, sizeof(ethh));
	hdr_p += sizeof(ethh);
	__builtin_memcpy(hdr_p, &ipv6h, sizeof(ipv6h));
	hdr_p += sizeof(ipv6h);
	__builtin_memcpy(hdr_p, &srh_alloc, sizeof(srh_alloc));

	bpf_redirect(vcfg->ifidx_wan, 0);
	return XDP_REDIRECT;
}

static inline int decap(struct xdp_md *ctx, struct cfg *vcfg)
{
	u8 *data_end = (u8 *)(long)ctx->data_end;
	u8 *data = (u8 *)(long)ctx->data;	
	_Alignas(16) char srh_alloc [sizeof(struct ipv6_sr_hdr) + sizeof (struct in6_addr)];
	if (data + sizeof(struct ethhdr)
			+ sizeof(struct ipv6hdr)
			+ sizeof(srh_alloc)
			> data_end){
		return XDP_PASS;
	}
	u8 *buf_head = data;
	bpf_trace_printk("x", 1);

	struct ethhdr *ethh = (struct ethhdr *)buf_head;
	if (ethh->h_proto != bpf_htons(ETH_P_IPV6)) {
		return XDP_PASS;
	}
	buf_head += sizeof(struct ethhdr);
	bpf_trace_printk("y", 1);	

	struct ipv6hdr *ip6h = (struct ipv6hdr *)buf_head;
	
	in6addr_dump("decap: dst ipv6 addr ", &(ip6h->daddr));
	in6addr_dump("decap: srv6 sid ", vcfg->d_sid);
	hex_dump("decap: nexthdr: ", &(ip6h->nexthdr), 4);

	bpf_printk("OK!!!!!!");
// ここから下が悪い
	if (__builtin_memcmp(&(ip6h->daddr), vcfg->d_sid, 16)) {
		bpf_trace_printk("a",1);
		dbg(ctx);
		return XDP_PASS;
	}

	buf_head += sizeof(struct ipv6hdr);
	bpf_trace_printk("b", 1);
	bpf_printk("O!");
	buf_head += sizeof(struct ipv6_sr_hdr);
	struct in6_addr *dsid = (struct in6_addr *)buf_head;
	if (__builtin_memcmp(dsid, vcfg->d_sid, 16)) {
		return XDP_PASS;
	}
	buf_head += sizeof(struct in6_addr);
	bpf_printk("P!");


	if (bpf_xdp_adjust_head(ctx, (buf_head-data))) {
		return XDP_PASS;
	}
	bpf_printk("Q!");

	bpf_redirect(vcfg->ifidx_lan, 0);
	return XDP_REDIRECT;
}

SEC("xdp")
int seg6_l2vpn(struct xdp_md *ctx)
{
	u8 key = 0;
	struct cfg *vcfg = (struct cfg*)bpf_map_lookup_elem(&seg6vpn_cfg_map, &key);
	char cfg_load_err[] = "configuration loading failure\n";
	if (!vcfg) {
		bpf_trace_printk(cfg_load_err, sizeof cfg_load_err);
		return XDP_PASS;
	}

	__u32 ifidx = ctx->ingress_ifindex;	
	if (ifidx == vcfg->ifidx_lan) {
		return encap(ctx, vcfg);
	} else if (ifidx == vcfg->ifidx_wan) {
		return decap(ctx, vcfg);
	return XDP_PASS;
	}
	return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
