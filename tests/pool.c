#include "pool.h"

#ifdef DEBUG
#include <stdio.h>
#endif

static bool __valid_addr(const sPool *const pool, const sPoolSeg *const fptr);
static pthread_mutex_t pool_mutex = PTHREAD_MUTEX_INITIALIZER;
sPool __pool;
static sPool *poolAddr = &__pool;

/**
 * Inicializaciya segmentov pula
 * sPool *const pool - ukazatel' na pul
 * return - true esli init proshel uspesshno
 * false - v sluchaye oshibki
 */
bool __init(sPool *const pool)
{
    static bool init_fl = false;

    if (init_fl)
    {
#ifdef DEBUG
        printf("Init uzhe proizveden\r\n");
#endif
        return false;
    }

    if (poolAddr != pool)
    {
#ifdef DEBUG
        printf("Neverniy adres pula\r\n");
#endif
        return false;
    }

    if (!pool)
    {
#ifdef DEBUG
        printf("&pool = NULL\r\n");
#endif
        return false;
    }

    if (sizeof(PTR_SIZE) > sizeof(sPoolSeg))
    {
#ifdef DEBUG
        printf("Razmer ukazatelya dolzhen bit' ne menshe razmera segmenta\r\n");
#endif
        return false;
    }

    pthread_mutex_lock(&pool_mutex);

    /* Связвывем элементы. Сделаем каст до указателя платформы и запишем туда адрес следующего сегмента */
    for (size_t i = 0; i < POOL_SIZE - 1; i++)
        *(PTR_SIZE *)(&pool->buff[i]) = (PTR_SIZE)(&(pool->buff[i + 1]));

    *((PTR_SIZE *)(&pool->buff[POOL_SIZE - 1])) = (PTR_SIZE)(NULL); // конец списка
    pool->freeSeg = pool->buff;                                     // указатель на свободный элемент

    /* ukazateli na nachalo i konec nuzhni dlya proverki pri free. t.k. adres mozhno peredat' lyboi */
    pool->pStart = &pool->buff[0];
    pool->pEnd = &pool->buff[POOL_SIZE];
    init_fl = true;
    pthread_mutex_unlock(&pool_mutex);

    return true;
}

/**
 * @brief
 *
 */
void *__alloc(sPool *const pool)
{
    sPoolSeg *ptrAlloc; // Возращаемый адрес сегмента

    if (!pool)
        return NULL; // Неверная передача параметров
    if (!pool->freeSeg)
        return NULL; // Конец пула

    pthread_mutex_lock(&pool_mutex);

    ptrAlloc = pool->freeSeg;                        // Свободный сегмент
    pool->freeSeg = *((sPoolSeg **)(pool->freeSeg)); // Передвинем указатель на следующий своюодный сегмент

    pthread_mutex_unlock(&pool_mutex);

    return ptrAlloc;
}

/**
 * sPool *pool - ukazatel' na pul
 * sPoolSeg *fptr - ukazatel' na videlenniy uchastok v pule
 * return -
 * NULL : esli osvobodili uchastok.
 * fptr tot zhe addr : esli nepravilno preredany parametri ili v sluchae esli vse segmenti svobodni
 * + vne diapazonov adresov ili adres ne kraten segmentu
 */
void *__free(sPool *const pool, sPoolSeg *fptr)
{
    if (!__valid_addr(pool, fptr))
        return fptr;

    pthread_mutex_lock(&pool_mutex);

    /* osvobozhdaemiy el-t ukazivaet na svobodniy v pule */
    *((sPoolSeg **)fptr) = pool->freeSeg;
    /* ukzatel' na svoboniy el-t teper' ukazivaet na tekushiy */
    pool->freeSeg = fptr;
    // fptr = NULL;
    pthread_mutex_unlock(&pool_mutex);

    return NULL;
}

/**
 *
 *
 */
static bool __valid_addr(const sPool *const pool, const sPoolSeg *const fptr)
{
    if (!pool || !fptr)
    {
#ifdef DEBUG
        printf("pool or fptr == NULL\r\n");
#endif
        return false;
    }

    if (fptr < pool->pStart || fptr > pool->pEnd)
    {
#ifdef DEBUG
        printf("vne diapozonov adresov\r\n");
#endif
        return false;
    }

    /* pust addr ptr0 = 0x10; ptr1 = 0x20 ...
    esli podat adres segmenta 0x09 budut problemi */

    if (((PTR_SIZE)pool->pEnd - (PTR_SIZE)fptr) % SEG_BYTE_SIZE != 0)
    {
#ifdef DEBUG
        printf("ne validniy ukazatel' na segmen\n");

#endif
        return false;
    }

    return true;
}