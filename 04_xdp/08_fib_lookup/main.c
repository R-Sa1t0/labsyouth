//go:build ignore

#include "main.h"

#include <linux/types.h>
#include <linux/bpf.h>

#include <bpf/bpf_helpers.h>

#include <linux/ip.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/socket.h>

SEC("xdp")
int xdp_main(struct xdp_md *ctx) {
/*
	char s0[] = "data: %08x, data_end: %08x, data_meta: %08x";
	bpf_trace_printk(s0, sizeof(s0), ctx->data, ctx->data_end, ctx->data_meta);
  char s1[] = "ingress_ifidx: %08x\n";
  bpf_trace_printk(s1, sizeof(s1), ctx->ingress_ifindex);
*/
  void *data_end = (void *)(long)ctx->data_end;
  void *data = (void *)(long)ctx->data;

  struct ether_header *ethhdr = data;
  if (data + sizeof(*ethhdr) > data_end) return XDP_ABORTED;
  if (ethhdr->type[0]==0x08 && ethhdr->type[1]==0x00) {
//    char s2[] = "IPv4!\n";
//    bpf_trace_printk(s2, sizeof(s2));
  } else {
    return XDP_PASS;
  }

  int offset = sizeof(*ethhdr);
  struct iphdr *iph = data + offset;
  if (data + offset + sizeof(*iph) > data_end) return XDP_ABORTED;
//  char ip_fmt[] = "ttl: %d\n";
//  bpf_trace_printk(ip_fmt, sizeof(ip_fmt), iph->ttl);

  int rc;
  struct bpf_fib_lookup fib_params;
  fib_params.family	= 2;
  fib_params.tos = iph->tos;
  fib_params.l4_protocol	= iph->protocol;
  fib_params.sport = 0;
  fib_params.dport = 0;
//  fib_params.tot_len = ntohs(iph->tot_len);
  fib_params.ipv4_src = iph->saddr;
  fib_params.ipv4_dst = iph->daddr;
  fib_params.ifindex = ctx->ingress_ifindex;

  int flag = 0;
//  rc = bpf_fib_lookup(ctx, &fib_params, sizeof(fib_params), flag);　
// 失敗する
/*

  char fmt0[] = "rc: %d\n";
  bpf_trace_printk(fmt0, sizeof(fmt0), rc);
*/


  /*
    char fmt[] = "type: %02x %02x\n";
    bpf_trace_printk(fmt, sizeof(fmt), ethhdr->type[0], ethhdr->type[1]);

    char s2[] = "%02x ";
    for (__u8 *i=(__u8 *)ethhdr; i < (__u8 *)(data+sizeof(*ethhdr)); i++) {
      bpf_trace_printk(s2, sizeof(s2), *i);
    }
  */




  return XDP_PASS;
}

char LICENSE[] SEC("license") = "Dual BSD/GPL";