//go:build ignore

#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

#define IFINDEX_A 2
#define IFINDEX_B 3

SEC("xdp")
int xdp_l2brg(struct xdp_md *ctx)
{
  int ifindex = 0;

  char s1[] = "0";
	bpf_trace_printk(s1, sizeof(s1));
  if (ctx->ingress_ifindex == IFINDEX_A){
    char s2[] = "1";
		bpf_trace_printk(s2, sizeof(s2));
		ifindex = IFINDEX_B;
	}else if (ctx->ingress_ifindex == IFINDEX_B) {
    char s3[] = "2";
		bpf_trace_printk(s3, sizeof(s3));
		ifindex = IFINDEX_A;
	}else{
		return XDP_DROP;
	}
  //  long stat = bpf_redirect_map(&devmap, ifindex, 0);
  char si[] = "ifindex: %d";
	bpf_trace_printk(si, sizeof(si), ifindex);

  int stat = bpf_redirect(ifindex, 0);
  char s4[] = "redirect: %d";
	bpf_trace_printk(s4, sizeof(s4), stat);

  return stat;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";