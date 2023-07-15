// #include <stdio.h>
#include <gtest/gtest.h>
#include "pool.h"

extern sPool __pool;

TEST(init_null_ptr, return_false)
{
    ASSERT_FALSE(pool.init(NULL));
}

TEST(init_invalid_addr, return_false)
{
    int i = 10;
    int *invalid_ptr = &i;
    invalid_ptr++;

    ASSERT_FALSE(pool.init((sPool *)invalid_ptr));
}

TEST(normal_init, return_true)
{
    ASSERT_TRUE(pool.init(&__pool));
}

TEST(init_two_times, return_false)
{
    ASSERT_FALSE(pool.init(&__pool));
}

TEST(free_random_ptr, return_null)
{
    ASSERT_EQ((sPoolSeg *)0x81f000aa, pool.free(&__pool, (sPoolSeg *)0x81f000aa));
}

TEST(alloc_all_pool, size_pool)
{

    sPoolSeg *ptrPool1[POOL_SIZE] = {NULL};
    size_t alloc_cnt = 0;

    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        ptrPool1[i] = (sPoolSeg *)pool.alloc(&__pool);
        if (ptrPool1[i] != NULL)
            alloc_cnt++;
    }

    ASSERT_EQ(alloc_cnt, POOL_SIZE);
}

TEST(try_alloc_from_empty_pool, zero_elements)
{

    sPoolSeg *ptrPool[POOL_SIZE] = {NULL};
    size_t alloc_cnt = 0, iter_cnt = 0;

    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        ptrPool[i] = (sPoolSeg *)pool.alloc(&__pool);
        if (ptrPool[i] != NULL)
            alloc_cnt++;
        iter_cnt++;
    }

    ASSERT_EQ(alloc_cnt, 0);
    ASSERT_EQ(iter_cnt, POOL_SIZE);
}

TEST(free_all_pull, pool_size_elements)
{

    size_t free_cnt = 0;

    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        if (NULL == (sPoolSeg *)pool.free(&__pool, ptrPool[i]))
            free_cnt++;
    }

    ASSERT_EQ(free_cnt, POOL_SIZE);
}

// int main(int argc, char const *argv[])
//{
//     /* */
//     pool.init(&__pool);
//
//     sPoolSeg *ptrPool1[POOL_SIZE] = {NULL};
//     for (size_t i = 0; i < POOL_SIZE; i++)
//         ptrPool1[i] = pool.alloc(&__pool);
//
//
//     printf("Test case 8: osvobozhdeniye vsego pula\r\n");
//
//     size_t alloc_cnt = 0;
//
//     for (size_t i = 0; i < POOL_SIZE; i++)
//     {
//         ptrPool1[i] = pool.free(&__pool, ptrPool1[i]);
//         if (ptrPool1[i] == NULL)
//             alloc_cnt++;
//     }
//
//     if (alloc_cnt == POOL_SIZE)
//         printf("OK\r\n\r\n");
//     else
//         printf("Error\r\n\r\n");
//
//     return 0;
// }

//
//    /* case 4 */
//    printf("Test case 4: init pula 2-i raz\r\n");
//    assert(pool.init(&__pool) == false);
//    printf("OK\r\n\r\n");
//    /* case 4 end */
//
//    /* case 5 */
//    printf("Test case 5: osvobozhdenie segmenta s randomnim adresom\r\n");
//    assert(pool.free(&__pool, (sPoolSeg *)0x81f000aa) == NULL);
//    printf("OK\r\n\r\n");
//    /* case 5 end */
//
//    /* case 6 */
//    printf("Test case 6: videlenie vsego pula\r\n");
//    sPoolSeg *ptrPool1[POOL_SIZE] = {NULL};
//    size_t alloc_cnt = 0;
//
//    for (size_t i = 0; i < POOL_SIZE; i++)
//    {
//        ptrPool1[i] = pool.alloc(&__pool);
//        if (ptrPool1[i] != NULL)
//            alloc_cnt++;
//    }
//
//    assert(alloc_cnt == POOL_SIZE);
//    printf("OK\r\n\r\n");
//    /* case 6 end */
//
//    /* */
//    printf("Test case 7: popitka videleniya iz pula, gde net svobodnih sigmentov\r\n");
//    sPoolSeg *ptrPool2[POOL_SIZE] = {NULL};
//    alloc_cnt = 0;
//
//    for (size_t i = 0; i < POOL_SIZE; i++)
//    {
//        ptrPool2[i] = pool.alloc(&__pool);
//        if (ptrPool2[i] != NULL)
//            alloc_cnt++;
//    }
//
//    if (alloc_cnt)
//        printf("Error\r\n\r\n");
//    else
//        printf("OK\r\n\r\n");
//
//    /* */
//    printf("Test case 8: osvobozhdeniye vsego pula\r\n");
//    alloc_cnt = 0;
//
//    for (size_t i = 0; i < POOL_SIZE; i++)
//    {
//        ptrPool1[i] = pool.free(&__pool, ptrPool1[i]);
//        if (ptrPool1[i] == NULL)
//            alloc_cnt++;
//    }
//
//    if (alloc_cnt == POOL_SIZE)
//        printf("OK\r\n\r\n");
//    else
//        printf("Error\r\n\r\n");
//
//    /* */
//    #define ITER    10000U
//    printf("Test case 9: randomnoe osvobozhdeniye i aloc (%d) iterciy\r\n", ITER);
//    size_t op, ii, free_cnt = 0;
//    alloc_cnt = 0;
//    for (size_t i = 0; i < ITER; i++)
//    {
//        ii = rand() % POOL_SIZE;
//        op = rand() % 2;
//
//        if (op)
//        {
//            if (ptrPool1[ii] == NULL)
//            {
//                ptrPool1[ii] = pool.alloc(&__pool);
//                ptrPool1[ii]->cnt = 0xFF;
//                alloc_cnt++;
//            }
//        }
//        else
//        {
//
//            if (ptrPool1[ii] != NULL)
//            {
//                ptrPool1[ii] = pool.free(&__pool, ptrPool1[ii]);
//                free_cnt++;
//            }
//        }
//    }

// return 0;
//}