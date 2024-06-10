#ifndef LEVEL_H
#define LEVEL
#include "arena.h"
#include "projectiles.h"
#include "tanks.h"
#include "mempool.h"

typedef struct Level_t {
    //MemoryPool_t *tanks;
    MemoryPool_t *projectiles;
    MemoryPool_t *mines;
    Arena *arena;
} Level_t;

Level_t *LevelInit();
void LevelStop(Level_t *g);

#endif