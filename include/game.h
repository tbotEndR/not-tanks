#ifndef GAME_H
#define GAME_H
#include "arena.h"
#include "projectiles.h"
#include "tanks.h"

typedef struct Game_t {
    TankPool *tanks;
    ProjectilePool *projectiles;
    Arena *arena;
} Game_t;

Game_t *LevelInit();
void LevelStop(Game_t *g);

#endif