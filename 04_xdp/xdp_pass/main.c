#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("main")
int xdp_main(struct xdp_md *ctx)
{
	return XDP_PASS;
}

char _license[] SEC("license") = "BSD";