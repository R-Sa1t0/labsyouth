#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "17_s3_def.h"

EXT* ext_p;
int ext_n;

void ext_begin(void){
    ext_p = malloc(sizeof(EXT));
    ext_n = 0;
}

void ext_end(void){
    for(int i=0; i<ext_n; i++) free(ext_p[i].ext);
    free(ext_p);
}

static void add_ext(char* path){
    char* file = strrchr(path, '.');
    if (file) file++; else file = path;
    
    char* ext=strrchr(file, '.');
    if (!ext) ext="";

    FILE* fp = fopen(path, "rb");
    if (fp){
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        fclose(fp);

        int i;
        for (i=0; i<ext_n && strcmp(ext_p[i].ext, ext); i++);

        if (i<ext_n){
            ext_p[i].count++;
            ext_p[i].size += size;
        }else{
            ext_n++;
            ext_p = realloc(ext_p, sizeof(EXT)*ext_n);

            ext_p[i].ext = malloc(strlen(ext)+1);
            strcpy(ext_p[i].ext, ext);

            ext_p[i].count = 1;
            ext_p[i].size = size;
        }
    }
}

void ext_find_files(char* path){
    DIR* dir = opendir(path);
    if (dir){
        struct dirent* entry;
        while((entry=readdir(dir)) != NULL){
            if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0){
                char s[strlen(path) + strlen(entry->d_name) + 2];
                sprintf(s, "%s/%s", path, entry->d_name);
                ext_find_files(s);
            }
        }
        closedir(dir);
    }else{
        add_ext(path);
    }
}

void ext_report(void){
    printf("%-14s %14s %14s %14s\n", "ext", "count", "size(total)", "size(average)");
    for(int i=0; i<ext_n; i++){
        EXT* p = &ext_p[i];
        printf("%-14s %14ld %14ld %14ld\n", p->ext, p->count, p->size, p->size/p->count);
    }
    puts("");
}