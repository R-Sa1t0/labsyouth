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
	__type(key, u8);
	__type(value, struct cfg);
} encap_cfg_map SEC(".maps");

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

static inline void dbg_printpkt(struct xdp_md *ctx) {
	bpf_printk("ingress_ifidx: %lu\n", ctx->ingress_ifindex);
}

static inline int encap(struct xdp_md *ctx, struct cfg *vcfg)
{
	return XDP_PASS;
}

static inline int decap(struct xdp_md *ctx, struct cfg *vcfg)
{
	return XDP_PASS;
}

SEC("xdp")
int seg6_l2vpn(struct xdp_md *ctx)
{
	u8 key = 0;
	struct cfg *vcfg = (struct cfg*)bpf_map_lookup_elem(&encap_cfg_map, &key);
	char cfg_load_err[] = "configuration loading failure\n";
	if (!vcfg) {
		bpf_trace_printk(cfg_load_err, sizeof cfg_load_err);
		dbg_printpkt(ctx);
		return XDP_PASS;
	}

	__u32 ifidx = ctx->ingress_ifindex;	
	if (ifidx == vcfg->ifidx_lan) {
		return encap(ctx, vcfg);
	} else if (ifidx == vcfg->ifidx_wan) {
		return decap(ctx, vcfg);
	}
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
