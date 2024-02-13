#pragma onece

typedef struct {
    char* ext;
    long count, size;
}EXT;

extern EXT* ext_p;
extern int ext_n;

void ext_begin(void);
void ext_end(void);
void ext_find_files(char* path);
void ext_report(void);