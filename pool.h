#include <stdint.h>  // types
#include <stdbool.h> // bool val
#include <pthread.h> // mutex 
#include <string.h>  // size_t

#ifndef _POOL_H_
#define _POOL_H_

#define DEBUG

/* Segmen pula */
typedef struct
{
    // Primer strukturi
    uint64_t cnt;
    uint8_t data[20];
} sPoolSeg;

/* Количество сегментов в пуле */
#define POOL_SIZE (6U)

/* Размер сегмента в байтах */
#define SEG_BYTE_SIZE (sizeof(sPoolSeg))

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

/* Все сегменты (Pool) */
typedef struct
{
    sPoolSeg * pStart , * pEnd;     //*
    sPoolSeg *freeSeg;              // Указатель на текущий свободный сегмент
    sPoolSeg buff[POOL_SIZE];       // Весь пул памяти
} sPool;

/* Инит буфера, обязателен перед работой с пулом */
bool __init(sPool * const pool);

/* Аллокция сегмента */
void *__alloc(sPool * const pool);

/* Освобождение сегмента в пуле */
void * __free(sPool * const pool, sPoolSeg *fptr);

/* Интерфейс работы с pool аллокатором */
static struct pool_interface
{
    bool (*init)(sPool * const pool);
    void *(*alloc)(sPool * const pool);
    void *(*free)(sPool * const pool, sPoolSeg *fptr);
} const pool = {__init, __alloc, __free };

#endif