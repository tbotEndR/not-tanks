#include "mempool.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MemoryPool_t *AllocPool(size_t blockSize, int n)
{
    MemoryPool_t *newPool = (MemoryPool_t*) malloc(sizeof(MemoryPool_t));
    newPool->pool = (void*) malloc(blockSize * n);
    char* poolCursor = newPool->pool;
    int fourByteBlocks = (n * blockSize) / 4;
    for (int i = 0; i < fourByteBlocks; i++)
    {
        poolCursor[i] = NULL;
    }
    newPool->nextFrees = StackCtor(n);
    newPool->blockSize = blockSize;
    newPool->blocks = n;
    return newPool;
}

void FreePool(MemoryPool_t *mp)
{
    free(mp->pool);
    StackDtor(mp->nextFrees);
    free(mp);
}

void *AllocBlock(MemoryPool_t *mp)
{
    int nextFree = mp->nextFrees->stack[mp->nextFrees->top];
    if (nextFree != -1)
    {
        void *newBlock = (intptr_t)mp->pool + mp->blockSize * nextFree;
        Pop(mp->nextFrees);
        return newBlock;
    }
    else return NULL;
}

void FreeBlock(void **block, MemoryPool_t *mp)
{
    int blockIndex = ((intptr_t)*block - (intptr_t)mp->pool) / mp->blockSize;
    char* blockStart = *block;
    for (int i = 0; i < mp->blockSize; i+=4)
    {
        blockStart += i;
        *blockStart = NULL;
        printf("writing NULL to 0x%x\n", blockStart);
    }
    *block = NULL;
    Push(mp->nextFrees, blockIndex);
}

Stack_t *StackCtor(int size)
{
    Stack_t *newStack = (Stack_t*) malloc(sizeof(Stack_t));
    newStack->stack = (int*) malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
    {
        newStack->stack[i] = size-1-i;
    }
    newStack->top = size-1;
    newStack->max = size;
    return newStack;
}

void StackDtor(Stack_t *stack)
{
    free(stack->stack);
    free(stack);
}

int Pop(Stack_t *stack)
{
    if (stack->top < 0) return NULL;
    int i = stack->stack[stack->top];
    stack->stack[stack->top] = -1;
    stack->top--;
    return i;    
}

void Push(Stack_t *stack, int i)
{
    if ((stack->top < stack->max-1) && (stack->stack[stack->top]) != -1) 
    {
        stack->stack[++stack->top] = i;
    }
}