#include <stdio.h>
#include <stdlib.h>

#include "liblist.h"

int main(void){
    printf("init\n");
    List* l = init_list();
    if (l == NULL) exit(1);
    display_list(l);

    printf("append x5\n");
    for(int32_t i=0; i<5; i++){
        append_cell(l, i);
    } 
    display_list(l);

    printf("delete_headcell x2\n");
    for(int32_t i=0; i<2; i++){
        delete_headcell(l);
    } 
    display_list(l);

    printf("append x3\n");
    for(int32_t i=99; i<103; i++){
        append_cell(l, i);
    } 
    display_list(l);

    printf("insert_cell(seek(l, 3), 999)\n");
    insert_cell(seek(l, 3), 999);
    display_list(l);

    printf("delete_tailcell x2\n");
    for(int i=0; i<2; i++) delete_tailcell(l);
    display_list(l);

    printf("delete_nextcell(l, seek(l, 1));\n");
    delete_nextcell(l, seek(l, 1));
    display_list(l);

    printf("delete_nextcell(l, l->head);\n");
    delete_nextcell(l, l->head);
    display_list(l);

    printf("delete_list()\n");
    delete_list(l);
    puts("OK");
}