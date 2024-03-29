#include "include/projectiles.h"

//  allocates a projectile pool of given size
ProjectilePool *PoolCtor(int size)
{
    ProjectilePool *newPool = (ProjectilePool*) malloc(sizeof(ProjectilePool));
    newPool->pool = (Projectile*) malloc(sizeof(Projectile) * size);
    newPool->size = size;
    newPool->nextFree = newPool->pool;
    newPool->arrEnd = newPool->pool + (size-1);
    for (int i = 0; i < size; i++)
    {
        newPool->pool[i].active = '0';
    }
    return newPool;
}

//  creates new Projectile if there is a free position in the array
void NewProjectile(ProjectilePool *pool, Vector3 position, Vector3 direction)
{
    if (pool->nextFree != NULL)
    {
        pool->nextFree->active = '1';
        pool->nextFree->direction = direction;
        pool->nextFree->position = position;
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

void PoolDtor(ProjectilePool* pool)
{
    free(pool->pool);
    free(pool);
}

void DeleteProjectile(ProjectilePool *pool, Projectile *p)
{
    p->active = '0';
    if ((p < pool->nextFree) || (pool->nextFree == NULL)) pool->nextFree = p;
}

void FreeProjectiles(ProjectilePool *pool)
{
    for (int i = 0; i < pool->size; i++)
    {
        DeleteProjectile(pool, &(pool->pool[i]));
    }
}

void UpdateProjectilePosition(ProjectilePool *pool)
{
   for (int i = 0; i < pool->size; i++)
   {
        if (pool->pool[i].active == '1') pool->pool[i].position = Vector3Add(pool->pool[i].position, Vector3Scale(Vector3Normalize(pool->pool[i].direction), 0.1f));
   }
}