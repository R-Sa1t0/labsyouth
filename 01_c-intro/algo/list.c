#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t data_t;
struct cell{
    data_t data;
    struct cell *next;
};

static struct cell * insert(struct cell* cell_ptr, data_t newval)
{
    struct cell *new_cell=malloc(sizeof(struct cell));
    if(new_cell==NULL) puts("malloc error!");

    new_cell->data=newval;
    new_cell->next=NULL;
    cell_ptr->next=new_cell;

    return new_cell;
}

static struct cell * delete(struct cell* cell_ptr)
{
    if(cell_ptr==NULL) return NULL;

    struct cell *next_cell = cell_ptr->next;
    free(cell_ptr);

    return next_cell;
}
static void delete2(struct cell* head, uint8_t n)
{
    struct cell *p = head;
    struct cell *p_old = NULL;

    for (uint8_t i = 0; i < n; i++) {
        if (p == NULL) return;
        p_old = p;
        p = p->next;
    }

    p_old->next = delete(p);
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
    struct cell c1,*head,*last;
    head=&c1;
    c1.data=100;
    c1.next=NULL;
    print(head);

    last=insert(&c1, 200);
    print(head);
    print(last);

    for(uint8_t i=0;i<10;i++) last=insert(last,i);
    print(head);

    head->next = delete(head->next);
    print(head);

    delete2(head, 3);
    print(head);
}