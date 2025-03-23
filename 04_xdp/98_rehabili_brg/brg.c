#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

#define IFIDX_ETH0 2
#define IFIDX_ETH1 3

SEC("xdp")
int xdp_brg(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	if (data + sizeof(struct ethhdr) > data_end) {
		return XDP_DROP;
	}

	int ifindex = ctx->ingress_ifindex;
	char msg[] = "ifidx: %d";
	bpf_trace_printk(msg, sizeof msg, ifindex);
	
	if (ifindex == IFIDX_ETH0) {
		bpf_redirect(IFIDX_ETH1, 0);
		return XDP_REDIRECT;
	} else if (ifindex == IFIDX_ETH1) {
		bpf_redirect(IFIDX_ETH0, 0);
		return XDP_REDIRECT;
	} 

	return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";
