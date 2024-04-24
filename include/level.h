#ifndef LEVEL_H
#define LEVEL
#include "arena.h"
#include "projectiles.h"
#include "tanks.h"

typedef struct Level_t {
    TankPool *tanks;
    ProjectilePool *projectiles;
    MinePool *mines;
    Arena *arena;
} Level_t;

Level_t *LevelInit();
void LevelStop(Level_t *g);

#endif