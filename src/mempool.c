#include "mempool.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//  returns a memory pool of elements-amount of blocks of size blockSize
MemoryPool_t *AllocateMemoryPool(size_t blockSize, int elements)
{
    MemoryPool_t *new_pool = (MemoryPool_t*) malloc(sizeof(MemoryPool_t));
    new_pool->memory = malloc(blockSize * elements);
    printf("Pool Memory starts at %x and ends at %x\n", (size_t)new_pool->memory, (size_t)(new_pool->memory) + (blockSize*(elements-1)));
    char *memory_cursor = (char*) new_pool->memory;
    for (int i = 0; i < elements; i++)
    {
        for (int n = 0; n < blockSize; n++)
        {
            *memory_cursor = NULL;
            memory_cursor++;
        }
    }
    new_pool->active_blocks = 0;
    new_pool->active_block_table = (int*) malloc(sizeof(int)*elements);
    new_pool->block_size = blockSize;
    new_pool->pool_size = elements;
    new_pool->next_free_stack = (int*) malloc(sizeof(int)*elements);
    for(int i = 0; i < elements; i++)
    {
        new_pool->next_free_stack[i] = elements-1-i;    //  fill stack in reverse -> top of stack is block 0
        new_pool->active_block_table[i] = 0;
    }
    new_pool->stack_top_index = elements-1;
    return new_pool;
}

void DeallocateMemoryPool(MemoryPool_t *pool)
{
    free(pool->next_free_stack);
    free(pool->memory);
    free(pool);    
}

//  returns a pointer to a NULL initialized block of memory with the pool's specified block size
void *AllocateBlock(MemoryPool_t *pool)
{
    if (pool->active_blocks < pool->pool_size)
    {
        int free_block_index = Pop(pool->next_free_stack, &(pool->stack_top_index));
        if (free_block_index == -1) return NULL;
        void *memory_block = pool->memory;
        memory_block = (void*)((char*)memory_block + pool->block_size*free_block_index);
        pool->active_blocks++;
        pool->active_block_table[free_block_index] = 1;
        printf("Allocating block at address 0x%x\n", (size_t)memory_block);
        printf("Active blocks: %d\n", pool->active_blocks);
        return memory_block;
    }
    else 
    {
        return NULL;
    }
}

//  deallocates block and returns it to the pool of available memory blocks
void DeallocateBlock(void *block, MemoryPool_t *pool)
{
    printf("Attempting deallocation of block at 0x%x.\n", (size_t)block);
    int block_index = ((size_t)block - (size_t)pool->memory) / pool->block_size;
    if (pool->active_block_table[block_index] == 1)
    {
        char *memory_cursor = (char*) block;
        for (int n = 0; n < pool->block_size; n++)
        {
            *memory_cursor = NULL;
            memory_cursor++;
        }
        pool->active_blocks--;
        pool->active_block_table[block_index] = 0;
        Push(pool->next_free_stack, block_index, pool);
    }
    else
    {
        printf("Illegal deallocation - block at 0x%x was not allocated.\n", (size_t)block);
    }
    
}

void DeallocateAllBlocks(MemoryPool_t *pool)
{
    void *memory_cursor = pool->memory;
    for (int i = 0; i < pool->pool_size; i++)
    {
        memory_cursor = (void*)((char*)pool->memory + pool->block_size * i);
        DeallocateBlock(memory_cursor, pool);
    }
}

//  Checks last byte for content and returns FALSE if it's NULL
int BlockIsActive(void *block, MemoryPool_t *pool)
{
    int block_index = ((size_t)block - (size_t)pool->memory) / pool->block_size;
    if (pool->active_block_table[block_index] == 0) return 0;
    else return 1;
}

//  returns the index of the next free memory block off of a pool's next_free_stack
int Pop(int *stack, int *stackTop)
{
    if (*stackTop >= 0)
    {
        int block_index = stack[*stackTop];
        printf("Popping %d at index %d from stack.\n", stack[*stackTop], *stackTop);
        stack[*stackTop] = -1;
        (*stackTop)--;
        return block_index;
    }
    else return -1;
}

//  pushes the index of a free'd memory block to the pool's next_free_stack
void Push(int *stack, int n, MemoryPool_t *pool)
{
    if (pool->stack_top_index < pool->pool_size - 1)
    {
        pool->stack_top_index++;
        stack[pool->stack_top_index] = n;
        printf("Pushing %d at index %d to stack.\n", n, pool->stack_top_index);     
    }
    else perror("STACK OVERFLOW");
}

void PrintMemoryPool(MemoryPool_t *pool)
{
    char *memory_cursor = (char*) pool->memory;
    printf("================\n");
    for (int i = 0; i < pool->pool_size; i++)
    {
        printf("Active table: [%3d]\n", pool->active_block_table[i]);
        for (int n = 0; n < pool->block_size; n++)
        {
            printf("[0x%x] : 0x%x \n", memory_cursor, *memory_cursor);
            memory_cursor++;
        }
        printf("================\n");
    }
}