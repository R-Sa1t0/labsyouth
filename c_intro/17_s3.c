#include <stdio.h>
#include "17_s3_def.h"

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    
    ext_begin();
    ext_find_files(argv[1]);
    ext_report();
    ext_end();
}