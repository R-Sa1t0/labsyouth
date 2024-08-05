// stack
#include <stdio.h>
#include <stdlib.h>

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
    u_int8_t cell_num;
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
static cell_t* add_cell(cell_t* c, data_t v){
    cell_t *nc=malloc(sizeof(cell_t));
    if (nc==NULL) puts("malloc error!");
    
    nc->val=v;
    nc->next=NULL;
    if(c!=NULL) c->next=nc;
    return nc;
}
static void del_cell(cell_t *p, u_int8_t n){
    if(p==NULL) return NULL;
    cell_t* nc=p->next;
    free(p);
    return nc;
}

static void push(stack_t* s, data_t v)
{
    if(s->root==NULL){
        s->last=add_cell(NULL, v);
        s->root=s->last;
    }else{
        s->last=add_cell(s->last, v);
    }
    s->cell_num++;
}

static data_t pop(stack_t *s)
{
    if(s->root==NULL){
        puts("empty");
    }else if(s->root==s->last){
        return (s->root)->val;
    }else{
        display(s->last);
        data_t t=(s->last)->val;
            
        return t;
    }
}

int main(void){
    stack_t s1={NULL, NULL,0};
    display(s1.root);

    for(int8_t i=0;i<10;i++) push(&s1, i);
    display(s1.root);

    for(int8_t i=0; i<5; i++)
    {
        printf("%d\n", pop(&s1));
        puts("");
    }
    display(s1.root);
}