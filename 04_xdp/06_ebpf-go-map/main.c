//go:build ignore

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

struct {
    __uint(type, BPF_MAP_TYPE_ARRAY); 
    __type(key, __u32);
    __type(value, __u64);
    __uint(max_entries, 1);
} pkt_count SEC(".maps");


SEC("xdp")
int xdp_ingress(struct xdp_md *ctx)
{
	__u32 key = 0;
	__u64 *count = bpf_map_lookup_elem(&pkt_count, &key);
	if (count != 0) {
		__sync_fetch_and_add(count, 1);
	}
	return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";