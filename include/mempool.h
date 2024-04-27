#ifndef MEMPOOL_H
#define MEMPOOL_H

typedef struct Stack_t {
    int *stack;
    int top;
    int max;
} Stack_t;

typedef struct MemoryPool_t {
    void *pool;
    Stack_t *nextList;
    int blockSize;
    int blocks;
} MemoryPool_t;

//  allocates a memory pool of n blocks of given blockSize
MemoryPool_t *AllocPool(int blockSize, int n);
void FreePool(MemoryPool_t *mp);
void *AllocBlock(MemoryPool_t *mp);
void FreeBlock(void *block, MemoryPool_t *mp);
void PrintPool(MemoryPool_t *mp);
Stack_t *StackCtor(int size);
void StackDtor(Stack_t *stack);
int Pop(Stack_t *stack);
void Push(Stack_t *stack, int i);
void PrintStack(Stack_t *stack);

#endif