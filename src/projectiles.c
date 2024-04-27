#include "projectiles.h"
#include "mempool.h"
#include <math.h>
#include <profileapi.h>

//  creates new Projectile_t if there is a free position in the array
void NewProjectile(MemoryPool_t *pool, Vector3 position, Vector3 direction)
{
    Projectile_t* newProjectile = (Projectile_t*) AllocBlock(pool);
    if (newProjectile != NULL)
    {
        newProjectile->active = '1';
        newProjectile->lives = 2;
        newProjectile->direction = Vector3Scale(Vector3Normalize(direction), 0.1f);
        newProjectile->position = position;
        pool->actives++;
    }
}

void DeleteProjectile(MemoryPool_t *pool, Projectile_t *p)
{
    p->active = '0';
    p->lives = 0;
    pool->actives--;
    if ((p < (Projectile_t*)pool->nextFree) || (pool->nextFree == NULL)) pool->nextFree = p;
}

void DeleteAllProjectiles(MemoryPool_t *pool)
{
    for (int i = 0; i < pool->poolSize; i++)
    {
        if (((Projectile_t*)pool)[i].active == '1') DeleteProjectile(pool, &((Projectile_t*)pool->pool)[i]);
    }
}

void UpdateProjectilePosition(MemoryPool_t *pool)
{
    for (int i = 0, counter = 0; (i < pool->poolSize) && (counter < pool->actives); i++)
    {
        if (counter >= pool->actives) break;
        if (((Projectile_t*)pool)[i].active == '1')
        {
            ((Projectile_t*)pool)[i].position = Vector3Add(((Projectile_t*)pool)[i].position, ((Projectile_t*)pool)[i].direction);
            counter++;
        } 
    }
}

void CheckProjectileCollision(MemoryPool_t *pool)
{
    for (int i = 0, counter = 0; (i < pool->poolSize) && (counter < pool->actives); i++)
    {
        if (((Projectile_t*)pool)[i].active == '1') 
        {
            // rudimentary check for wall collision and ricochet
            if ((((Projectile_t*)pool)[i].position.x >= 38.0f) || (((Projectile_t*)pool)[i].position.x <= -38.0f)) 
            {
                if (((Projectile_t*)pool)[i].lives == 1) DeleteProjectile(pool, &((Projectile_t*)pool->pool)[i]);
                else
                {   
                    ((Projectile_t*)pool)[i].direction.x *= -1;
                    ((Projectile_t*)pool)[i].lives--;
                }
            }
            if ((((Projectile_t*)pool)[i].position.z >= 24.0f) || (((Projectile_t*)pool)[i].position.z <= -24.0f)) 
            {
                if (((Projectile_t*)pool)[i].lives == 1) DeleteProjectile(pool, &((Projectile_t*)pool->pool)[i]);
                else
                {   
                    ((Projectile_t*)pool)[i].direction.z *= -1;
                    ((Projectile_t*)pool)[i].lives--;
                }
            }

            // check for collisions with other projectiles
           counter++;
        }
    }
}

void DrawProjectiles(MemoryPool_t *pool)
{
    for (int i = 0, counter = 0; (i < pool->poolSize) && (counter < pool->actives); i++)
    {
        if (((Projectile_t*)pool)[i].active == '1') 
        {
            //DrawSphere(pool->pool[i].position, 0.3f, LIGHTGRAY);
            DrawCube(((Projectile_t*)pool)[i].position, 0.3f, 0.3f, 0.3f, LIGHTGRAY);
            DrawCubeWires(((Projectile_t*)pool)[i].position, 0.3f, 0.3f, 0.3f, RED);

            counter++;
        }
    }
}

void NewMine(MemoryPool_t *pool, Vector3 position)
{
    if (pool->nextFree != NULL)
    {
        LARGE_INTEGER t1, freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&t1);

        ((Mine_t*)pool->nextFree)->active = '1';
        ((Mine_t*)pool->nextFree)->endTime = t1.QuadPart / freq.QuadPart + 10.0;
        ((Mine_t*)pool->nextFree)->position = position;
        pool->actives++;
        do
        {
            (pool->nextFree)++;
            if (pool->nextFree > pool->arrEnd) 
            {
                pool->nextFree = NULL;
                break;
            }
             
        } while (((Mine_t*)pool->nextFree)->active != '0');
    }
}

void DeleteMine(MemoryPool_t *pool, Mine_t *m)
{
    m->active = '0';
    pool->actives--;
    if ((m < (Mine_t*)pool->nextFree) || (pool->nextFree == NULL)) pool->nextFree = m;
}
void DeleteAllMines(MemoryPool_t *pool)
{
    for (int i = 0; i < pool->poolSize; i++)
    {
        if (((Mine_t*)pool->pool)[i].active == '1') DeleteMine(pool, &((Mine_t*)pool->pool)[i]);
    }
}
void DrawMines(MemoryPool_t *pool)
{
    for (int i = 0, counter = 0; (i < pool->poolSize) && (counter < pool->actives); i++)
    {
        if (((Mine_t*)pool->pool)[i].active == '1') 
        {
            DrawSphere(((Mine_t*)pool->pool)[i].position, ((Mine_t*)pool->pool)[i].size, RED);
            counter++;
        }
    }
}

void CheckMineTimers(MemoryPool_t *pool)
{
    LARGE_INTEGER t1, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t1);
    for (int i = 0, counter = 0; (i < pool->poolSize) && (counter < pool->actives); i++)
    {
        if (((Mine_t*)pool->pool)[i].active == '1') 
        {
            if (((Mine_t*)pool->pool)[i].endTime <= t1.QuadPart/freq.QuadPart) DeleteMine(pool, &((Mine_t*)pool->pool)[i]);
        }
    }
}
