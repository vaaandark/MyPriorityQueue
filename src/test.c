#include <stdio.h>
#include "FibonacciHeap.h"

#define TIMES 10000

void print_top(PToFibHeap h)
{
    ValueType val;
    Status sts = top(h, &val);
    if (sts == ERROR) {
        printf("It's an empty heap!\n");
    } else {
        printf("top: %d\n", val);
    }
}

int main(void)
{
    PToFibHeap h = init();
    int i;
    for (i = 0; i < TIMES; i++) {
        int cmd, num;
        scanf("%d%d", &cmd, &num);
        if (cmd == 0) {
            pop(h);
        } else {
            push(h, num);
        }
        printf("size: %d\n", size(h));
        print_top(h);
    }
    delete(h);
    return 0;
}