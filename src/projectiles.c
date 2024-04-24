#include "projectiles.h"
#include <math.h>
#include <profileapi.h>

//  allocates a Projectile_t pool of given size
ProjectilePool *ProjectilePoolCtor(int size)
{
    ProjectilePool *newPool = (ProjectilePool*) malloc(sizeof(ProjectilePool));
    newPool->pool = (Projectile_t*) malloc(sizeof(Projectile_t) * size);
    newPool->size = size;
    newPool->nextFree = newPool->pool;
    newPool->arrEnd = newPool->pool + (size-1);
    newPool->actives = 0;
    for (int i = 0; i < size; i++)
    {
        newPool->pool[i].active = '0';
        newPool->pool[i].lives = 0;
        newPool->pool[i].size = 1.0f;
    }
    return newPool;
}

//  creates new Projectile_t if there is a free position in the array
void NewProjectile(ProjectilePool *pool, Vector3 position, Vector3 direction)
{
    if (pool->nextFree != NULL)
    {
        pool->nextFree->active = '1';
        pool->nextFree->lives = 2;
        pool->nextFree->direction = Vector3Scale(Vector3Normalize(direction), 0.1f);
        pool->nextFree->position = position;
        pool->actives++;
        do
        {
            (pool->nextFree)++;
            if (pool->nextFree > pool->arrEnd) 
            {
                pool->nextFree = NULL;
                break;
            }
             
        } while (pool->nextFree->active != '0');
    }
}

void ProjectilePoolDtor(ProjectilePool* pool)
{
    free(pool->pool);
    free(pool);
}

void DeleteProjectile(ProjectilePool *pool, Projectile_t *p)
{
    p->active = '0';
    p->lives = 0;
    pool->actives--;
    if ((p < pool->nextFree) || (pool->nextFree == NULL)) pool->nextFree = p;
}

void DeleteAllProjectiles(ProjectilePool *pool)
{
    for (int i = 0; i < pool->size; i++)
    {
        if (pool->pool[i].active == '1') DeleteProjectile(pool, &(pool->pool[i]));
    }
}

void UpdateProjectilePosition(ProjectilePool *pool)
{
    for (int i = 0, counter = 0; (i < pool->size) && (counter < pool->actives); i++)
    {
        if (counter >= pool->actives) break;
        if (pool->pool[i].active == '1')
        {
            pool->pool[i].position = Vector3Add(pool->pool[i].position, pool->pool[i].direction);
            counter++;
        } 
    }
}

void CheckProjectileCollision(ProjectilePool *pool)
{
    for (int i = 0, counter = 0; (i < pool->size) && (counter < pool->actives); i++)
    {
        if (pool->pool[i].active == '1') 
        {
            // rudimentary check for wall collision and ricochet
            if ((pool->pool[i].position.x >= 38.0f) || (pool->pool[i].position.x <= -38.0f)) 
            {
                if (pool->pool[i].lives == 1) DeleteProjectile(pool, &pool->pool[i]);
                else
                {   
                    pool->pool[i].direction.x *= -1;
                    pool->pool[i].lives--;
                }
            }
            if ((pool->pool[i].position.z >= 24.0f) || (pool->pool[i].position.z <= -24.0f)) 
            {
                if (pool->pool[i].lives == 1) DeleteProjectile(pool, &pool->pool[i]);
                else
                {   
                    pool->pool[i].direction.z *= -1;
                    pool->pool[i].lives--;
                }
            }

            // check for collisions with other projectiles
           counter++;
        }
    }
}

void DrawProjectiles(ProjectilePool *pool)
{
    for (int i = 0, counter = 0; (i < pool->size) && (counter < pool->actives); i++)
    {
        if (pool->pool[i].active == '1') 
        {
            //DrawSphere(pool->pool[i].position, 0.3f, LIGHTGRAY);
            DrawCube(pool->pool[i].position, 0.3f, 0.3f, 0.3f, LIGHTGRAY);
            DrawCubeWires(pool->pool[i].position, 0.3f, 0.3f, 0.3f, RED);

            counter++;
        }
    }
}

//  yes all of this is mostly identical to projectiles, I'll figure out a cleaner way to do this in the future

MinePool *MinePoolCtor(int size)
{
    MinePool *newPool = (MinePool*) malloc(sizeof(MinePool));
    newPool->pool = (Mine_t*) malloc(sizeof(Mine_t) * size);
    newPool->size = size;
    newPool->nextFree = newPool->pool;
    newPool->arrEnd = newPool->pool + (size-1);
    newPool->actives = 0;
    for (int i = 0; i < size; i++)
    {
        newPool->pool[i].active = '0';
        newPool->pool[i].endTime = 0.0;
        newPool->pool[i].size = 1.0f;
    }
    return newPool;
}

void MinePoolDtor(MinePool *pool)
{
    free(pool->pool);
    free(pool);
}

void NewMine(MinePool *pool, Vector3 position)
{
    if (pool->nextFree != NULL)
    {
        LARGE_INTEGER t1, freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&t1);

        pool->nextFree->active = '1';
        pool->nextFree->endTime = t1.QuadPart / freq.QuadPart + 10.0;
        pool->nextFree->position = position;
        pool->actives++;
        do
        {
            (pool->nextFree)++;
            if (pool->nextFree > pool->arrEnd) 
            {
                pool->nextFree = NULL;
                break;
            }
             
        } while (pool->nextFree->active != '0');
    }
}
void DeleteMine(MinePool *pool, Mine_t *m)
{
    m->active = '0';
    pool->actives--;
    if ((m < pool->nextFree) || (pool->nextFree == NULL)) pool->nextFree = m;
}
void DeleteAllMines(MinePool *pool)
{
    for (int i = 0; i < pool->size; i++)
    {
        if (pool->pool[i].active == '1') DeleteMine(pool, &(pool->pool[i]));
    }
}
void DrawMines(MinePool *pool)
{
    for (int i = 0, counter = 0; (i < pool->size) && (counter < pool->actives); i++)
    {
        if (pool->pool[i].active == '1') 
        {
            DrawSphere(pool->pool[i].position, pool->pool[i].size, RED);
            counter++;
        }
    }
}

void CheckMineTimers(MinePool *pool)
{
    LARGE_INTEGER t1, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t1);
    for (int i = 0, counter = 0; (i < pool->size) && (counter < pool->actives); i++)
    {
        if (pool->pool[i].active == '1') 
        {
            if (pool->pool[i].endTime <= t1.QuadPart/freq.QuadPart) DeleteMine(pool, &(pool->pool[i]));
        }
    }
}
