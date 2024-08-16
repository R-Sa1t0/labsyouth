#include "liblinklist.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t
display_list(List* l)
{
    printf("head: %p, tail: %p, len: %zu\n", l->head, l->tail, l->n);
    Cell* c = l->head;
    size_t n = 0;

    while (c != NULL) {
        printf("addr: %p, data: %d, next: %p\n", c, c->data, c->next);
        c = c->next;
        n++;
    }
    if (n != l->n)
        printf("ERROR : n != l->n, n: %zu\n", n);

    puts("");
    return true;
}

List*
init_list()
{
    List* l = (List*)malloc(sizeof(List));
    if (l == NULL) {
        return NULL;
    }

    l->head = NULL;
    l->tail = NULL;
    l->n = 0;
    return l;
}

Cell*
seek(List* l, size_t n)
{
    if (n == 0)
        return NULL;
    //    if(n==l->n) printf("WARN : seek(&l, %zu) is tail", l->n);

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
    if (nc == NULL)
        return false;
    nc->data = v;
    nc->next = NULL;

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
insert_cell(List* l, Cell* c, data_t v)
{
    Cell* nc = (Cell*)malloc(sizeof(Cell));
    if (nc == NULL)
        return false;

    nc->data = v;
    nc->next = c->next;
    c->next = nc;
    l->n++;

    return true;
}

uint8_t
delete_headcell(List* l)
{
    if (l->head == NULL) {
        return false; // List is empty
    } else if (l->head == l->tail) {
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
        return false;
    } else if (l->head == l->tail) {
        free(l->head);
        l->head = l->tail = NULL;
    } else {
        Cell* prev_cell = seek(l, (l->n) - 2);
        free(l->tail);
        prev_cell->next = NULL;
        l->tail = prev_cell;
    }
    l->n--;

    return true;
}

uint8_t
delete_nextcell(List* l, Cell* c)
{
    if (c == NULL || c->next == NULL) {
        return false; // Next cell not found.
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
delete_cell(List* l, Cell* c)
{
    if (l == NULL || c == NULL)
        return false;

    if (c == l->head) {
        Cell* tmp = l->head;
        l->head = l->head->next;
        if (l->head == l->tail) {
            l->head = l->tail = NULL;
        }
        free(tmp);
    } else if (c == l->tail) {
        Cell* prevcell = seek(l, (l->n) - 2);
        free(l->tail);
        prevcell->next = NULL;
        l->tail = prevcell;
    } else {
        Cell *tmp, *prevcell;
        tmp = prevcell = NULL;
        tmp = l->head;
        while (tmp != c) {
            prevcell = tmp;
            tmp = l->head->next;
        }
        prevcell->next = tmp->next;
        free(tmp);
    }

    l->n--;
    return true;
}

uint8_t
delete_list(List* l)
{
    if (l->head == NULL) {
        return false;
    } else if (l->tail == NULL) {
        return false;
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
