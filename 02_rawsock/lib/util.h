#pragma once

#include <net/ethernet.h>
#include <net/if.h>
#include <sys/ioctl.h>

int get_lladdr(struct ether_addr *addr, const char *nic_name);
