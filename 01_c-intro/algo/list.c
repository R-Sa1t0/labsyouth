#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct cell {
    uint8_t value;
    struct cell **next;
};
typedef struct cell cell;

void insert(cell **cell_ptr, uint8_t new_val){
    cell *new_cell=(cell *)malloc(sizeof(cell));
    new_cell->value=new_val;
    new_cell->next=*cell_ptr;
    *cell_ptr=new_cell;
}
void delete(cell **cell_ptr){
    cell *target=*cell_ptr;
    *cell_ptr=target->next;
    free(target);
}
void print_cell(cell **head_ptr){
    printf("head addr : %x\n", head_ptr);
    if(head_ptr==NULL) return;
    printf("%x\n", &head_ptr);
    cell *p=head_ptr;
    while(true){
        if((p->next)==NULL||p==NULL) break;
        printf("addr : %x / value : %d\n", p, p->value);
        p=p->next;
    }
}

int main(void){
    cell *head=NULL, **p;
    p=&head;
    print_cell(p);
    /*
    for(uint8_t i=0;i<5;i++){
        insert(p,i);
        p=&((*p)->next);
    }
    */
}