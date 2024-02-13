#include <dirent.h>
#include <stdio.h>
#include <string.h>

void find_files(char* path){
    DIR* dir = opendir(path);
    if (dir){
        struct dirent* entry;
        while((entry = readdir(dir)) != NULL){
            if (strcmp(".", entry->d_name) != 0 && strcmp("..", entry->d_name) != 0){
                char s[strlen(path) + strlen(entry->d_name) + 2];
                sprintf(s, "%s/%s", path, entry->d_name);
                find_files(s);
            }
        }
        closedir(dir);
    }else{
        puts(path);
    }
}

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    find_files(argv[1]);
}