#ifndef MEMPOOL_H
#define MEMPOOL_H

typedef struct MemoryPool_t {
    void *pool;
    void *nextFree;
    void *arrEnd;
    int actives;
    int poolSize;
    int blockSize;
} MemoryPool_t;

//  allocates a memory pool of n blocks of given blockSize
MemoryPool_t *AllocPool(int blockSize, int n);
void FreePool(MemoryPool_t *mp);
void *AllocBlock(MemoryPool_t *mp);
void FreeBlock(void *block);
void UpdateNextFree(MemoryPool_t *mp);

#endif