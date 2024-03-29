#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

typedef struct Projectile{
    Vector3 position;
    Vector3 direction;
    char active;
} Projectile;

typedef struct ProjectilePool{
    int size;
    int actives;
    Projectile *pool;
    Projectile *nextFree;
    Projectile *arrEnd;
} ProjectilePool;

ProjectilePool *PoolCtor(int size);
void PoolDtor(ProjectilePool* pool);
void NewProjectile(ProjectilePool *pool, Vector3 position, Vector3 direction);
void DeleteProjectile(ProjectilePool *pool, Projectile *p);
void DeleteAllProjectiles(ProjectilePool *pool);
void UpdateProjectilePosition(ProjectilePool *pool);
void CheckProjectileCollision(ProjectilePool *pool);
void DrawProjectiles(ProjectilePool *pool);

#endif