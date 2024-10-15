#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("main")
int xdp_main(struct xdp_md *ctx)
{
	char s1[] = "Hello!!\n";
	bpf_trace_printk(s1, sizeof(s1));

	char s2[] = "Hello int: %d, %d, %d\n";
	__u8 i = 254;
	bpf_trace_printk(s2, sizeof(s2), i, i, i);

	char s3[] = "Hello hex: %02x%02x%02x\n";
	bpf_trace_printk(s3, sizeof(s3), i, i, i);
	bpf_trace_printk("Hello hex: %02x%02x%02x\n", 25, i, i, i);

	return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";