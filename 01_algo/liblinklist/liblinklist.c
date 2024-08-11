#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "liblinklist.h"

//エラーするときのスタックトレースを取りたい
void
errExit(const char* msg)
{
    printf("ERROR: %s\n", msg);
    exit(1);
}
void
warn(const char* msg)
{
    printf("WARN: %s\n", msg);
}

uint8_t 
display_list(List* l)
{
    printf("head: %p, tail: %p, len: %zu\n", l->head, l->tail, l->n);
    Cell* c = l->head;

    while (c != NULL) {
        printf("addr: %p, data: %d, next: %p\n", c, c->data, c->next);
        c=c->next;
    }
    puts("");
    return true;
}

List*
init_list()
{
    List* l=(List*)malloc(sizeof(List));
    if (l == NULL) {
        errExit("Malloc Error");
//        return NULL;
    }

    l->head = NULL;
    l->tail = NULL;
    l->n = 0;
    return l;
}

Cell* seek(List* l, size_t n)
{
    if(n==0) warn("seek(&l, 0) is head");
    if(n==l->n) printf("WARN : seek(&l, %zu) is tail", l->n);

    Cell* c = l->head;
    size_t len = 0;

    while (c != NULL) {
        if (len == n)
            return c;
        
        c = c->next;
        len++;
    }

    return NULL;
}

uint8_t
append_cell(List* l, data_t v)
{
    Cell* nc = (Cell*)malloc(sizeof(Cell));
    if (nc == NULL) errExit("malloc error");
    nc->data = v;
    nc->next= NULL;

    if (l->head == NULL) {
        l->head = l->tail = nc;
    } else {
        l->tail->next = nc;
        l->tail = nc;
    }

    l->n++;

    return true;
}

uint8_t
insert_cell(Cell* c, data_t v)
{
    Cell* nc = (Cell*)malloc(sizeof(Cell));
    if (nc == NULL) errExit("malloc error");
    
    nc->data = v;
    nc->next = c->next;
    c->next = nc;

    return true;
}

uint8_t
delete_headcell(List* l)
{
    if (l->head == NULL) {
        errExit("List is empty");
//        return false;
    } else if (l->head == l-> tail) {
        free(l->head);
        l->head = l->tail = NULL;
        l->n = 0;
        return true;
    }

    Cell* tmp = l->head;
    l->head = l->head->next;
    free(tmp);
    l->n--;

    return true;
}

uint8_t
delete_tailcell(List* l)
{
    if (l->head == NULL) {
        errExit("List is empty");
        // return false
    } else if (l->head == l->tail){
        free(l->head);
        l->head = l->tail = NULL;
    } else {
        Cell* prev_cell = seek(l, (l->n)-1);
        free(l->tail);
        l->tail = prev_cell;
        l->tail->next = NULL;
    }
    l->n--;

    return true;    
}

uint8_t
delete_nextcell(List* l, Cell* c)
{
    if (c == NULL || c->next == NULL) {
        errExit("Next cell not found.");
        //return false;
    }

    Cell* tmp = c->next;
    if (c->next == l->tail) {
        l->tail = c;
    }
    c->next = c->next->next;

    free(tmp);
    l->n--;

    return true;
}

uint8_t
delete_list(List* l){
    if (l->head == NULL){
        errExit("List(head) is NULL");
    } else if (l->tail == NULL) {
        errExit("List(tail) is NULL");
    } else {
        while (true) {
            Cell* tmp = l->head;
            l->head = l->head->next;
            free(tmp);
            l->n--;
            if (l->head == NULL) {
                l->head = l->tail = NULL;
                l->n = 0;
                break;
            }
        }
    }
    free(l);
    l = NULL;

    return true;
}



