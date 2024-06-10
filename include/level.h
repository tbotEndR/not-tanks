#ifndef LEVEL_H
#define LEVEL
#include "arena.h"
#include "projectiles.h"
#include "tanks.h"
#include "mempool.h"

typedef struct Qtree_t {
    struct Qtree_t *child1, *child2, *child3, *child4;     //  +x+y, +x-y, -x-y, -x+y
    void *entityPool;
} Qtree_t;

typedef struct Level_t {
    MemoryPool_t *tanks;
    MemoryPool_t *projectiles;
    MemoryPool_t *mines;
    Arena *arena;
} Level_t;

Level_t *LevelInit();
void LevelStop(Level_t *g);
Qtree_t *CreateQuadTree(Level_t *level);
void UpdateQuadTree(Qtree_t *qtree);
void DeleteQuadTree(Qtree_t *qtree);

#endif