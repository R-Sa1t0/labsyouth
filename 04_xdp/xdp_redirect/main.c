#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

#define IFINDEX_1 2
#define IFINDEX_2 3

SEC("xdp")
int xdp_main(struct xdp_md *ctx)
{
	int ifindex = 0;

	if (ctx->ingress_ifindex == IFINDEX_1){
		ifindex = IFINDEX_2;
	}else if (ctx->ingress_ifindex == IFINDEX_2) {
		ifindex = IFINDEX_1;
	}else{
		return XDP_DROP;	
	}

	return bpf_redirect(ifindex, 0);

//	return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";