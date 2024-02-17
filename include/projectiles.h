#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

typedef struct projectile{
    Vector3 position;
    Vector3 direction;
    char active;
} projectile;

typedef struct projectilePool{
    int size;
    projectile *pool;
    projectile *nextFree;
    projectile *arrEnd;
} projectilePool;

projectilePool *PoolCtor(int size);
void NewProjectile(projectilePool *pool, Vector3 position, Vector3 direction);
void DeleteProjectile(projectilePool *pool, projectile *p);
void FreeProjectiles(projectilePool *pool);
void UpdateProjectilePosition(projectilePool *pool);

#endif