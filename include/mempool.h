#ifndef MEMPOOL_H
#define MEMPOOL_H
#include <stddef.h>

typedef struct MemoryPool_t{
    void* memory;
    size_t block_size;
    int active_blocks;
    int *active_block_table;
    int pool_size;
    int *next_free_stack;
    int stack_top_index;
} MemoryPool_t;

MemoryPool_t *AllocateMemoryPool(size_t blockSize, int elements);
void DeallocateMemoryPool(MemoryPool_t *pool);
void *AllocateBlock(MemoryPool_t *pool);
void DeallocateBlock(void *block, MemoryPool_t *pool);
void DeallocateAllBlocks(MemoryPool_t *pool);
int BlockIsActive(void* block, MemoryPool_t *pool);
int Pop(int *stack, int *stackTop);
void Push(int *stack, int n, MemoryPool_t *pool);

void PrintMemoryPool(MemoryPool_t *pool);

#endif