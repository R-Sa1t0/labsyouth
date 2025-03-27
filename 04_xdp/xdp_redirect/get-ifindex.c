#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

int main(int argc, char* argv[])
{
  if (argc < 2) {
    fprintf(stderr, "get-ifindex usage : %s {{if-name}}\n", argv[0]);
    return -1;
  }

  struct ifreq ifr;
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
      fprintf(stderr, "Failed to create socket\n");
      return -1;
  }
  
  strncpy(ifr.ifr_name, argv[1], IFNAMSIZ - 1);
  if (ioctl(fd, SIOCGIFINDEX, &ifr) == -1) {
    fprintf(stderr, "ioctl SIOCGIFINDEX failed: %s\n", strerror(errno));
    return -2;
  }
  
  printf("%s ifindex is %d\n", argv[1], ifr.ifr_ifindex);
}