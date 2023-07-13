#include "pool.h"
#include "test_lib.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{

    extern sPool __pool;
    printf("Test begin\r\n\r\n");

    /* */
    printf("Test case 1: init NULL\r\n");
    if (pool.init(NULL))
        printf("Error\r\n\r\n");
    else
        printf("OK\r\n\r\n");

    /* */
    int i = 10;
    int *invalid_ptr = &i;
    invalid_ptr++;

    printf("Test case 2: init invalid addr\r\n");
    if (pool.init((sPool *)invalid_ptr))
        printf("Error\r\n\r\n");
    else
        printf("OK\r\n\r\n");

    /* */
    printf("Test case 3: normal init\r\n");
    if (pool.init(&__pool))
        printf("OK\r\n\r\n");
    else
        printf("Error\r\n\r\n");

    /* */
    printf("Test case 4: 2i init\r\n");
    if (pool.init(&__pool))
        printf("Error\r\n\r\n");
    else
        printf("OK\r\n\r\n");

    /* */
    printf("Test case 5: osvobozhdenie segmenta s randomnim adresom\r\n");
    if (pool.free(&__pool, (sPoolSeg *)0x81f000aa))
        printf("OK\r\n\r\n");
    else
        printf("Error\r\n\r\n");

    /* */
    printf("Test case 6: videlenie vsego pula\r\n");
    sPoolSeg *ptrPool1[POOL_SIZE] = {NULL};
    size_t alloc_cnt = 0;

    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        ptrPool1[i] = pool.alloc(&__pool);
        if (ptrPool1[i] != NULL)
            alloc_cnt++;
    }

    if (alloc_cnt == POOL_SIZE)
        printf("OK\r\n\r\n");
    else
        printf("Error\r\n\r\n");

    /* */
    printf("Test case 7: popitka videleniya iz pula, gde net svobodnih sigmentov\r\n");
    sPoolSeg *ptrPool2[POOL_SIZE] = {NULL};
    alloc_cnt = 0;

    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        ptrPool2[i] = pool.alloc(&__pool);
        if (ptrPool2[i] != NULL)
            alloc_cnt++;
    }

    if (alloc_cnt)
        printf("Error\r\n\r\n");
    else
        printf("OK\r\n\r\n");

    return 0;
}