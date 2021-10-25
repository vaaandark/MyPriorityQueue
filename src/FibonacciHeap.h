#ifndef _FIBONACCIHEAP_H
#define _FIBONACCIHEAP_H

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR 1

#define MAXDEGREE 16

typedef int ValueType;
typedef unsigned int Status;
typedef unsigned int Bool;
typedef struct HeapNode *Position;
typedef struct HeapNode *LinkList;
typedef struct FibonacciHeap *PToFibHeap;

struct HeapNode
{
    ValueType val;
    Position pre;
    Position next;
    Position child;
    unsigned int degree;
};

struct FibonacciHeap
{
    Position min;
    unsigned int size;
};

PToFibHeap init(void);
Status top(PToFibHeap h, ValueType *val);
Bool empty(PToFibHeap h);
unsigned int size(PToFibHeap h);
void push(PToFibHeap h, ValueType val);
void pop(PToFibHeap h);
void clear(PToFibHeap h);
void delete(PToFibHeap h);

static Position new_node(ValueType val);
static void delete_node_from_list(Position p);
static void cat_nodes(Position p1, Position p2);
static Position be_son(Position p1, Position p2);
static void consolidate(PToFibHeap h);

// void print_link_list(Position p);

#endif /* _FIBONACCIHEAP_H */