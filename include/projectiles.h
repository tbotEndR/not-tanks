#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"
#include "raymath.h"
#include "mempool.h"
#include <stdlib.h>

typedef struct Projectile_t{
    Vector3 position;
    Vector3 direction;
    float size;
    int lives;
    char active;
} Projectile_t;

typedef struct Mine_t {
    Vector3 position;
    double endTime;
    float size;
    char active;
} Mine_t;

void NewProjectile(MemoryPool_t *pool, Vector3 position, Vector3 direction);
void DeleteProjectile(MemoryPool_t *pool, Projectile_t *p);
void DeleteAllProjectiles(MemoryPool_t *pool);
void UpdateProjectilePosition(MemoryPool_t *pool);
void CheckProjectileCollision(MemoryPool_t *pool);
void DrawProjectiles(MemoryPool_t *pool);

void NewMine(MemoryPool_t *pool, Vector3 position);
void DeleteMine(MemoryPool_t *pool, Mine_t *m);
void DeleteAllMines(MemoryPool_t *pool);
void CheckMineTimers(MemoryPool_t *pool);
void DrawMines(MemoryPool_t *pool);

#endif