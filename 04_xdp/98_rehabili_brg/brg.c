#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>

struct {
	__uint(type, BPF_MAP_TYPE_DEVMAP);
	__uint(key_size, sizeof(__u32));
	__uint(value_size, sizeof(__u32));
	__uint(max_entries, 256);
} tx_port SEC(".maps");

#define IF_ETH0 0
#define IF_ETH1 1

SEC("xdp")
int xdp_bridge_func(struct xdp_md *ctx)
{
	void *data_end = (void *)(long)ctx->data_end;
	void *data = (void *)(long)ctx->data;
	struct ethhdr *eth = data;
	__u32 ifindex;

	if (data + sizeof(struct ethhdr) > data_end) {
		return XDP_DROP;
	}

	int eth0_ifi = IF_ETH0;
	__u32 *ingress_ifindex = bpf_map_lookup_elem(&tx_port, &eth0_ifi);
	if (ingress_ifindex && ctx->ingress_ifindex == *ingress_ifindex) {
		ifindex = IF_ETH1;
	} else {
		ifindex = IF_ETH0;
	}

	return bpf_redirect_map(&tx_port, ifindex, 0);
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";

