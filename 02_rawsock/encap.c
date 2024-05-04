#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <linux/in6.h>

#define BUFFER_SIZE 1500
typedef struct{
    uint8_t v[BUFFER_SIZE];
    size_t len;
}Buffer;
void buffer_init(Buffer *buf){
    memset(buf->v, 0, BUFFER_SIZE);
    buf->len=0;
}
void buffer_append(Buffer *buf, const uint8_t *data, size_t data_size){
    if (buf->len+data_size>BUFFER_SIZE){
        fprintf(stderr, "BUF_ERR: buffer full\n");
        exit(1);
    }
    memcpy(buf->v+buf->len, data, data_size);
    buf->len+=data_size;
}
void buffer_print(Buffer *buf){
    for (int i=0; i<buf->len; i++) printf("%02x ", ((uint8_t *)buf->v)[i]);
    puts("");
}

int get_macaddr(char *mac_addr, char *nic_name){
    struct ifreq ifr ={};
    return 0; 
}

typedef struct {
    struct in6_addr ip6_srcaddr;
    struct in6_addr ip6_dstaddr;
    char *lan_nic_name;
    char *wan_nic_name;
}arg;
arg parse_arg(int argc, char *argv[]){
    arg result;
    return result;
}


int main(int argc, char *argv[]){

}
