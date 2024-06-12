#pragma once

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <net/ethernet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include <linux/if_packet.h>

int get_lladdr(struct ether_addr *addr, const char *nic_name);
int parse_macaddr(struct ether_addr *addr, const char *addr_str);
int open_rawsock_pernic(int *fd, const char* nic_name);