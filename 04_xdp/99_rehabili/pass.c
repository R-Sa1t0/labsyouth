//go:build ignore

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int xdp_pass(struct xdp_md *ctx)
{
        return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";

