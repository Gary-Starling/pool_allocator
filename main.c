#include "pool.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    sPool myPool;

    if (!pool.init(&myPool))
        EXIT_FAILURE;

    /* test */
    for (size_t i = 0; i < 1000; i++)
    {
        sPoolSeg *my_data1 = pool.alloc(&myPool);
        my_data1->data[0] = 'T';
        my_data1->cnt = 1;
        sPoolSeg *my_data2 = pool.alloc(&myPool);
        my_data2->data[0] = 'E';
        my_data2->cnt = 2;
        sPoolSeg *my_data3 = pool.alloc(&myPool);
        my_data3->data[0] = 'S';
        my_data3->cnt = 3;
        sPoolSeg *my_data4 = pool.alloc(&myPool);
        my_data4->data[0] = 'T';
        my_data4->cnt = 4;
        sPoolSeg *my_data5 = pool.alloc(&myPool);
        my_data5->data[0] = '1';
        my_data5->cnt = 5;
        sPoolSeg *my_data6 = pool.alloc(&myPool);
        my_data6->data[0] = 'N';
        my_data6->cnt = 6;
        sPoolSeg *my_data7 = pool.alloc(&myPool);

        my_data6 = pool.free(&myPool, my_data6);
        my_data2 = pool.free(&myPool, my_data2);
        my_data1 = pool.free(&myPool, my_data1);
        my_data4 = pool.free(&myPool, my_data4);
        my_data3 = pool.free(&myPool, my_data3);
        my_data5 = pool.free(&myPool, my_data5);
        my_data5 = pool.free(&myPool, my_data5);
        my_data7 = pool.free(&myPool, my_data7);

        pool.free(&myPool, (sPoolSeg *)0x800000aa);
    }

    /* test */

    return EXIT_SUCCESS;
}
