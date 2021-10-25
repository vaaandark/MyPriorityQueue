
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMES 10000

int main(void)
{
    int cmd;
    srand((unsigned)time(NULL));
    int i;
    for (i = 0; i < TIMES; i++) {
        cmd = rand()%5;
        printf("%d\n%d\n", cmd, rand() % 50);
    }
    return 0;
}