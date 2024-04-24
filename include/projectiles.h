#ifndef PROJECTILES_H
#define PROJECTILES_H
#include "raylib.h"
#include "raymath.h"
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
    time_t countdown;
    float size;
    char active;
} Mine_t;

typedef struct ProjectilePool{
    int size;
    int actives;
    Projectile_t *pool;
    Projectile_t *nextFree;
    Projectile_t *arrEnd;
} ProjectilePool;

ProjectilePool *ProjectilePoolCtor(int size);
void ProjectilePoolDtor(ProjectilePool* pool);
void NewProjectile(ProjectilePool *pool, Vector3 position, Vector3 direction);
void DeleteProjectile(ProjectilePool *pool, Projectile_t *p);
void DeleteAllProjectiles(ProjectilePool *pool);
void UpdateProjectilePosition(ProjectilePool *pool);
void CheckProjectileCollision(ProjectilePool *pool);
void DrawProjectiles(ProjectilePool *pool);

#endif