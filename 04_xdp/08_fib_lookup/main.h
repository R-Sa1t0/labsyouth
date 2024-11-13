#ifndef XDP_PROG_H
#define XDP_PROG_H

#include <linux/types.h>

struct ether_header {
  __u8 dst_addr[6];
  __u8 src_addr[6];
  __u8 type[2];
};



#endif