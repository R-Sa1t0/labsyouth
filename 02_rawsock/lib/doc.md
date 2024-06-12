## Utils
### buf.h : Buffer Management
```
typedef struct{
    uint8_t v[BUFFER_SIZE];
    size_t len;
}Buffer;

int buffer_init(Buffer *buf);
int buffer_append(Buffer *buf, const uint8_t *data, const size_t data_size);
void buffer_print(const Buffer *buf);
```

### util.h
```
int get_lladdr(struct ether_addr *addr, const char *nic_name);
```