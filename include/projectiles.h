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
} Projectile_t;

typedef struct Mine_t {
    Vector3 position;
    double endTime;
    float size;
} Mine_t;

void NewProjectile(MemoryPool_t *projectiles, Vector3 position, Vector3 direction);
void DeleteProjectile(MemoryPool_t *projectiles, Projectile_t *p);
void DeleteAllProjectiles(MemoryPool_t *projectiles);
void UpdateProjectilePosition(MemoryPool_t *projectiles);
void CheckProjectileCollision(MemoryPool_t *projectiles);
void DrawProjectiles(MemoryPool_t *projectiles);

void NewMine(MemoryPool_t *mines, Vector3 position);
void DeleteMine(MemoryPool_t *mines, Mine_t *p);
void DeleteAllMines(MemoryPool_t *mines);
void CheckMineCollision(MemoryPool_t *mines);
void DrawMines(MemoryPool_t *mines);
void CheckMineTimers(MemoryPool_t *mines);


#endif