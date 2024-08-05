// stack
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef int8_t data_t;
typedef struct cell
{
    data_t val;
    struct cell* next;
} cell_t;
typedef struct stack
{
    cell_t* root;
    cell_t* last;
    uint8_t n;
} stack_t;


static void display(cell_t* p)
{
    printf("head addr : %p\n", (void *)p);
    cell_t* t=p;
    while(t!=NULL)
    {
        printf("addr : %p / data : %d / next : %p\n", (void*)t, t->val, (void*)t->next);
        t=t->next;
    }
    puts("");
}
static cell_t* add_cell(cell_t* c, data_t v)
{
    cell_t *nc=malloc(sizeof(cell_t));
    if (nc==NULL) puts("malloc error!");
    
    nc->val=v;
    nc->next=NULL;
    if(c!=NULL) c->next=nc;
    return nc;
}
static void del_cell(stack_t *s, uint8_t n)
{
    cell_t *p, *pb;
    p=s->root;
    for(uint8_t i=0;i<n;i++){
        if(p==NULL) return;
        pb=p;
        p=p->next;
    }
    if(p==s->last){
        s->last = pb;
        s->last->next=NULL;
    }else if(pb!=NULL){
        pb->next = p->next;
    }else{
        s->root=p->next;
    }
    free(p);
}

static void push(stack_t* s, data_t v)
{
    if(s->root==NULL){
        s->last=add_cell(NULL, v);
        s->root=s->last;
    }else{
        s->last=add_cell(s->last, v);
    }
    s->n++;
}

static data_t pop(stack_t *s)
{
    data_t t;
    if(s->root==NULL){
        puts("empty");
    }else if(s->root==s->last){
        t=(s->root)->val;
        s->root=s->last=NULL;
    }else{
        t=(s->last)->val;
        del_cell(s, (s->n)-1);
    }
    s->n--;
    return t;
}

int main(void){
    stack_t s1={NULL, NULL,0};
    display(s1.root);

    for(int8_t i=0;i<5;i++) push(&s1, i);
    display(s1.root);

    for(int8_t i=0; i<5; i++)
    {
        printf("poped : %d\n", pop(&s1));
        display(s1.root);
        puts("");
    }
}