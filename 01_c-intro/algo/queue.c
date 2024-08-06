#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

static void display(cell_t* p){
    printf("head addr : %p\n", (void *)p);
    cell_t*t=p;
    while(t!=NULL)
    {
        printf("addr: %p, data: %d, next: %p\n", (void*)t, t->val, (void*)t->next);
        t=t->next;
    }
    puts("");
}

static void push(queue_t* q, data_t v){
    cell_t *nc=malloc(sizeof(cell_t));
    if(nc==NULL) puts("malloc error");

    nc->val=v;
    nc->next=q->head;
    if(q->head==NULL) q->tail=nc;
    q->head=nc;
    q->n++;
}

static data_t pop(queue_t* q){
    data_t t;
    cell_t *p, *pb;
    if(q->head==NULL){
        puts("queue empty");
    }else if(q->head==q->tail){
        t=q->head->val;
    }else{
        t=q->tail->val;
    }

    p=q->head;
    for(uint8_t i=0;i<(q->n)-1;i++){
        if(p==NULL) break;
        pb=p;
        p=p->next;
    }
    //printf("p: %p, pd: %p, n: %d\n", p, pb, q->n);

    if(q->head==p){
        q->head=q->tail=NULL;
        return t;
    }

    pb->next=NULL;
    q->tail=pb;
    q->n--;

    free(p);

    /*


        if(p==(q->head)){
            q->head=q->tail=NULL;
        }else if(p==(q->tail)){
            pb->next=NULL;
        }else{
            pb->next=NULL;
        }
        free(pb);
    */

    return t;
}

int main(void){
    queue_t q={NULL, NULL, 0};
    for(int8_t i=0;i<15;i++) push(&q, i);
    display(q.head);

    for(int8_t i=0;i<20;i++) {
        printf("%d\n", pop(&q));
        display(q.head);
        puts("");
    }
    
}