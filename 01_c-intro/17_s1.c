#include <dirent.h>
#include <stdio.h>
#include <string.h>

void find_files(char* path){
    DIR* dir = opendir(path);
    if (dir){
        struct dirent* entry;
        while((entry = readdir(dir)) != NULL){
            pritf("%s/%s\n", path, entry->d_name);
        }
        closedir(dir);
    }
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    find_files(argv[1]);
}