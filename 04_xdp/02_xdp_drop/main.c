#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int xdp_main(struct xdp_md *ctx)
{
	return XDP_DROP;
}

char _license[] SEC("license") = "BSD";