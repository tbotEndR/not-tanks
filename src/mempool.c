#include "mempool.h"
#include <stdlib.h>
#include <stdio.h>

MemoryPool_t *AllocPool(int blockSize, int n)
{
    MemoryPool_t *newPool = (MemoryPool_t*) malloc(sizeof(MemoryPool_t));
    newPool->pool = (void*) malloc(blockSize * n);
    newPool->nextList = StackCtor(n);
    newPool->blockSize = blockSize;
    newPool->blocks = n;
    return newPool;
}

void FreePool(MemoryPool_t *mp)
{
    free(mp->pool);
    StackDtor(mp->nextList);
    free(mp);
}

void *AllocBlock(MemoryPool_t *mp)
{
    int nextFree = mp->nextList->stack[mp->nextList->top];
    if (nextFree != -1)
    {
        void *newBlock = mp->pool + mp->blockSize * nextFree;
        Pop(mp->nextList);
        return newBlock;
    }
}

void FreeBlock(void *block, MemoryPool_t *mp)
{
    int blockIndex = (block - mp->pool) / mp->blockSize;
    block = (void*) NULL;
    Push(mp->nextList, blockIndex);
}

void PrintPool(MemoryPool_t *mp)
{
    for (int i = 0; i < mp->blocks; i++)
    {
        printf("Block %d: [ 0x%x ]\n", i, mp->pool + mp->blockSize * i);
    }
}

Stack_t *StackCtor(int size)
{
    Stack_t *newStack = (Stack_t*) malloc(sizeof(Stack_t));
    newStack->stack = (int*) malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
    {
        newStack->stack[i] = i;
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

void PrintStack(Stack_t *stack)
{
    for(int i = 0; i < stack->max; i++)
    {
        printf("[%d]:%d\n", i, stack->stack[i]);
    }
    printf("stack top: %d\n", stack->top);
}