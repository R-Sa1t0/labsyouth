#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t data_t;
typedef struct cell{
    data_t val;
    struct cell* next;
}cell_t;
typedef struct queue{
    cell_t* head;
    cell_t* tail;
    uint8_t n;
}queue_t;

static void display(cell_t* p)
{
    printf("head addr : %p\n", (void *)p);
    cell_t*t=p;
    while(t!=NULL)
    {
        printf("addr: %p, data: %d, next: %p\n", (void*)t, t->val, (void*)t->next);
        t=t->next;
    }
    puts("");
}

static int8_t push(queue_t* q, data_t v)
{
    cell_t *nc=malloc(sizeof(cell_t));
    if(nc==NULL){
        puts("malloc error!");
        return false;
    }

    nc->val=v;
    nc->next=q->head;
    if(q->head==NULL) q->tail=nc;
    q->head=nc;
    q->n++;

    return true;
}

static int8_t pop(queue_t* q, data_t *v)
{
    cell_t *p, *pb;
    if(q->head==NULL){
        puts("queue empty");
        return false;
    }else if(q->head==q->tail){
        *v=q->head->val;
    }else{
        *v=q->tail->val;
    }

    p=q->head;
    for(uint8_t i=0;i<(q->n)-1;i++){
        if(p==NULL) return false;
        pb=p;
        p=p->next;
    }
    //printf("p: %p, pd: %p, n: %d\n", p, pb, q->n);

    if(q->head==p){
        q->head=q->tail=NULL;
        return true;
    }

    pb->next=NULL;
    q->tail=pb;
    q->n--;

    free(p);
    return true;
}

int main(void)
{
    queue_t q={NULL, NULL, 0};
    for(int8_t i=0;i<5;i++) push(&q, i);
    display(q.head);

    for(int8_t i=0;i<5;i++) {
        data_t t;
        if(pop(&q, &t)!=true) return -1;
        printf("%d\n", t);
        display(q.head);
        puts("");
    }
}