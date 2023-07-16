#include <stdint.h>  // types
#include <stdbool.h> // bool val
#include <pthread.h> // mutex 
#include <string.h>  // size_t

#ifndef _POOL_H_
#define _POOL_H_

//#define DEBUG

/* Config */

/* Segmen pula */
typedef struct
{
    // Primer strukturi
    uint64_t cnt;
    uint8_t data[20];
} sPoolSeg;


#define POOL_SIZE (10U)
#define SEG_BYTE_SIZE (sizeof(sPoolSeg))

/* Config end */

/* Нам нужен размер указателя */
#if INTPTR_MAX == INT64_MAX
#define PTR_SIZE uint64_t
#elif INTPTR_MAX == INT32_MAX
#define PTR_SIZE uint32_t
#elif INTPTR_MAX == INT16_MAX
#define PTR_SIZE uint16_t
#else
#error Oshibka razmera ukazatelya
#endif

/* structura pula  */
typedef struct
{
    sPoolSeg * pStart , * pEnd;     // nuzhno dlya proverki v diapazone pula
    sPoolSeg *freeSeg;              // ptr na tekushii svobodniy segment 
    sPoolSeg buff[POOL_SIZE];       // bufer pula
} sPool;

/* Init, nuzhen pered nachalom raboti  */
bool __init(sPool * const pool);

/* Segment allocation  */
void *__alloc(sPool * const pool);

/* Segment free */
void * __free(sPool * const poolNULL, sPoolSeg *fptr);

/* Interface */
static struct pool_interface
{
    bool (*init)(sPool * const pool);
    void *(*alloc)(sPool * const pool);
    void *(*free)(sPool * const pool, sPoolSeg *fptr);
} const pool = {__init, __alloc, __free };
//TODO: deinit?

#endif