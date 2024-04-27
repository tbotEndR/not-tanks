#include "mempool.h"
#include <stdlib.h>

MemoryPool_t *AllocPool(int blockSize, int n)
{
    MemoryPool_t *newPool = (MemoryPool_t*) malloc(sizeof(MemoryPool_t));
    newPool->blockSize = blockSize;
    newPool->poolSize = n * blockSize;
    newPool->actives = 0;
    newPool->pool = malloc(blockSize * n);
    newPool->nextFree = newPool->pool;
    newPool->arrEnd = newPool->pool + (n * blockSize);
    return newPool;
}

void FreePool(MemoryPool_t *mp)
{
    free(mp->pool);
    free(mp);
}

void *AllocBlock(MemoryPool_t *mp)
{
    if (mp->nextFree != NULL)
    {
        void *newBlock = mp->nextFree;
        mp->actives++;
        UpdateNextFree(mp);
        return newBlock;
    }
}

void FreeBlock(void *block)
{
    block = NULL;

}

void UpdateNextFree(MemoryPool_t *mp)
{
    do
    {
        (mp->nextFree)++;
        if (mp->nextFree > mp->arrEnd) 
        {
            mp->nextFree = NULL;
            break;
        }
            
    } while (mp->nextFree != NULL);
}
