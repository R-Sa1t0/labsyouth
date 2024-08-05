#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int data_t;
struct cell{
    data_t data;
    struct cell *next;
};

static void insert(struct cell* cell_ptr, data_t newval)
{
    struct cell *new_cell=malloc(sizeof(struct cell));
    if(new_cell==NULL) return;

    new_cell->data=newval;
    new_cell->next=NULL;
    cell_ptr->next=new_cell;
}

static void print(struct cell *head_ptr)
{
    printf("head addr : %p\n", (void*)head_ptr);
    struct cell *p=head_ptr;
    while (p!=NULL)
    {
        printf("addr : %p / data : %d / next : %p\n", (void*)p, p->data, (void*)p->next);
        p=p->next;
    }
    puts("");
}


int main(void)
{
    struct cell c1,*head;
    head=&c1;
    c1.data=100;
    c1.next=NULL;
    print(head);

    insert(&c1, 200);
    print(head);
}