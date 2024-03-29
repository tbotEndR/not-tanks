#include "include/projectiles.h"

//  allocates a projectile pool of given size
ProjectilePool *PoolCtor(int size)
{
    ProjectilePool *newPool = (ProjectilePool*) malloc(sizeof(ProjectilePool));
    newPool->pool = (Projectile*) malloc(sizeof(Projectile) * size);
    newPool->size = size;
    newPool->nextFree = newPool->pool;
    newPool->arrEnd = newPool->pool + (size-1);
    newPool->actives = 0;
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

void PoolDtor(ProjectilePool* pool)
{
    free(pool->pool);
    free(pool);
}

void DeleteProjectile(ProjectilePool *pool, Projectile *p)
{
    p->active = '0';
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
   for (int i = 0; i < pool->size; i++)
   {
        if (pool->pool[i].active == '1') pool->pool[i].position = Vector3Add(pool->pool[i].position, Vector3Scale(Vector3Normalize(pool->pool[i].direction), 0.1f));
   }
}

void CheckProjectileCollision(ProjectilePool *pool)
{
    for (int i = 0; (i < pool->size) && (i+1 < pool->actives); i++)
    {
        if (pool->pool[i].active == '1') 
        {
            // rudimentary check for wall collision and ricochet
            if ((pool->pool[i].position.x >= 38.0f) || (pool->pool[i].position.x <= -38.0f)) pool->pool[i].direction.x *= -1;
            else if ((pool->pool[i].position.z >= 24.0f) || (pool->pool[i].position.z <= -24.0f)) pool->pool[i].direction.z *= -1;

            // check for collisions with other projectiles
            for (int f = i+1; f < pool->size; f++)
            {
                if (pool->pool[f].active == '1')
                {
                    if ((pool->pool[i].position.x - pool->pool[f].position.x <= 0.1f) && (pool->pool[i].position.z - pool->pool[f].position.z <= 0.1f))
                    {
                        DeleteProjectile(pool, &(pool->pool[f]));
                        DeleteProjectile(pool, &(pool->pool[i]));
                        break;
                    }
                }
            }
        }
    }
}

void DrawProjectiles(ProjectilePool *pool)
{
    for (int i = 0; (i < pool->size) && (i+1 < pool->actives); i++)
    {
        if (pool->pool[i].active == '1') 
        {
            DrawSphere(pool->pool[i].position, 0.3f, LIGHTGRAY);
        }
    }
}