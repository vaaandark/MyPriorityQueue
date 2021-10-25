#include "FibonacciHeap.h"

PToFibHeap init(void)
{
    PToFibHeap h = (PToFibHeap)malloc(sizeof(struct FibonacciHeap));
    h->min = NULL;
    h->size = 0;
    return h;
}

Status top(PToFibHeap h, ValueType *val)
{
    if (!h || !h->min) {
        return ERROR;
    }
    else {
        *val = h->min->val;
        return OK;
    }
}

Bool empty(PToFibHeap h)
{
    if (!h->min) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

unsigned int size(PToFibHeap h)
{
    return h->size;
}

void push(PToFibHeap h, ValueType val)
{
    if (!h) {
        return;
    }
    else if (!h->min) {
        h->min = new_node(val);
    }
    else {
        Position p = new_node(val);
        cat_nodes(h->min, p);
        if (h->min->val > val) {
            h->min = p;
        }
    }
    h->size++;
}

void pop(PToFibHeap h)
{
    if (!h->min) {
        return;
    }
    Position del = h->min;
    if (h->min->next == h->min) {
        h->min = h->min->child;
    } else {
        h->min = h->min->next;
        delete_node_from_list(del);
        cat_nodes(del->child, h->min);
    }
    free(del);
    del = NULL;
    consolidate(h);
    h->size--;
}

static Position new_node(ValueType val)
{
    Position p = (Position)malloc(sizeof(struct HeapNode));
    p->child = NULL;
    p->next = p->pre = p;
    p->degree = 0;
    p->val = val;
    return p;
}

static void delete_node_from_list(Position p)
{
    if (!p) {
        return;
    }
    p->next->pre = p->pre;
    p->pre->next = p->next;
}

// void print_link_list(Position p)
// {
//     Position i = p;
//     do {
//         printf("%d ", i->val);
//         i = i->next;
//     } while (i != p);
//     printf("\n");
// }

static void cat_nodes(Position p1, Position p2)
{
    if (!p1 || !p2) {
        return;
    }
    p1->pre->next = p2;
    p2->pre->next = p1;
    Position tmp = p1->pre;
    p1->pre = p2->pre;
    p2->pre = tmp;
}

static Position be_son(Position p1, Position p2)
{
    if (!p1) {
        return p2;
    }
    if (!p2) {
        return p1;
    }
    if (p1->val > p2->val) {
        Position tmp = p1;
        p1 = p2;
        p2 = tmp;
    }
    p2->pre = p2->next = p2;
    delete_node_from_list(p2);
    if (!p1->child) {
        p1->child = p2;
    } else {
        cat_nodes(p1->child, p2);
    }
    p1->degree++;
    return p1;
}

static void consolidate(PToFibHeap h)
{
    if (!h->min || h->min == h->min->next) {
        return;
    }
    Position i = h->min;
    Position addr[MAXDEGREE] = {NULL};
    do {
        Position next = i->next;
        int d = i->degree;
        while (addr[d]) {
            i = be_son(addr[d], i);
            addr[d] = NULL;
            d++;
        }
        addr[d] = i;
        i = next;
    } while (i != h->min);

    h->min = NULL;

    int k;
    for (k = 0; k < MAXDEGREE; k++) {
        if (addr[k]) {
            addr[k]->pre = addr[k]->next = addr[k];
            if (!h->min) {
                h->min = addr[k];
            }
            else {
                cat_nodes(h->min, addr[k]);
                if (addr[k]->val < h->min->val) {
                    h->min = addr[k];
                }
            }
        }
    }
}

void clear(PToFibHeap h)
{
    if (!h) {
        return;
    }
    while (h->min) {
        pop(h);
    }
    h->size = 0;
}

void delete(PToFibHeap h)
{
    clear(h);
    if (h) {
        free(h);
    }
}

