#include "projectiles.h"
#include "mempool.h"
#include <math.h>
#include <profileapi.h>

void NewProjectile(MemoryPool_t *projectiles, Vector3 position, Vector3 direction)
{
    Projectile_t* newProjectile = (Projectile_t*) AllocateBlock(projectiles);
    if (newProjectile != NULL)
    {
        newProjectile->lives = 2;
        newProjectile->direction = Vector3Scale(Vector3Normalize(direction), 0.1f);
        newProjectile->position = position;
    }
}

void DeleteProjectile(MemoryPool_t *projectiles, Projectile_t *p)
{
    DeallocateBlock(p, projectiles);
}

void DeleteAllProjectiles(MemoryPool_t *projectiles)
{
    DeallocateAllBlocks(projectiles);
}

void UpdateProjectilePosition(MemoryPool_t *projectiles)
{
    if (projectiles->active_blocks > 0)
    {
        Projectile_t *projectile_cursor = (Projectile_t*) projectiles->memory;
        for (int i = 0, counter = 0; (i < projectiles->pool_size); i++)
        {
            if (counter >= projectiles->active_blocks) break;
            if (BlockIsActive((void*)projectile_cursor, projectiles))
            {
                projectile_cursor->position = Vector3Add(projectile_cursor->position, projectile_cursor->direction);
                counter++;
            } 
            projectile_cursor++;
        }
    }
    
}

void CheckProjectileCollision(MemoryPool_t *projectiles)
{
    if (projectiles->active_blocks > 0)
    {
        Projectile_t *projectile_cursor = (Projectile_t*) projectiles->memory;
        for (int i = 0; (i < projectiles->pool_size); i++)
        {
            if (BlockIsActive((void*)projectile_cursor, projectiles)) 
            {
                // rudimentary check for wall collision and ricochet
                if ((projectile_cursor->position.x >= 38.0f) || (projectile_cursor->position.x <= -38.0f)) 
                {
                    if (projectile_cursor->lives == 1) 
                    {
                        DeleteProjectile(projectiles, projectile_cursor);
                        break;
                    }
                    else
                    {   
                        projectile_cursor->direction.x *= -1;
                        projectile_cursor->lives--;
                    }
                }
                if ((projectile_cursor->position.z >= 24.0f) || (projectile_cursor->position.z <= -24.0f)) 
                {
                    if (projectile_cursor->lives == 1) 
                    {
                        DeleteProjectile(projectiles, projectile_cursor);
                        break;
                    }
                    else
                    {   
                        projectile_cursor->direction.z *= -1;
                        projectile_cursor->lives--;
                    }
                }

                // check for collisions with other projectiles
            }
            projectile_cursor++;
        }
    }
    
}

void DrawProjectiles(MemoryPool_t *projectiles)
{
    if (projectiles->active_blocks > 0)
    {
        Projectile_t *projectile_cursor = (Projectile_t*) projectiles->memory;
        for (int i = 0, counter = 0; (i < projectiles->pool_size) && (counter < projectiles->active_blocks); i++)
        {
            if (BlockIsActive((void*)projectile_cursor, projectiles)) 
            {
                DrawCube(projectile_cursor->position, 0.3f, 0.3f, 0.3f, LIGHTGRAY);
                DrawCubeWires(projectile_cursor->position, 0.3f, 0.3f, 0.3f, RED);
                counter++;
            }
            projectile_cursor++;
        }
    }
}

void NewMine(MemoryPool_t *mines, Vector3 position)
{
    Mine_t *newMine = AllocateBlock(mines);
    if (newMine != NULL)
    {
        LARGE_INTEGER t1, freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&t1);
        newMine->endTime = t1.QuadPart / freq.QuadPart + 10.0;
        newMine->position = position;
        newMine->size = 0.5;
    }
}

void DeleteMine(MemoryPool_t *mines, Mine_t *m)
{
    DeallocateBlock(m, mines);
}

void DeleteAllMines(MemoryPool_t *mines)
{
    DeallocateAllBlocks(mines);
}

void DrawMines(MemoryPool_t *mines)
{
    if (mines->active_blocks > 0)
    {
        Mine_t* mine_cursor = (Mine_t*) mines->memory;
        for (int i = 0, counter = 0; (i < mines->pool_size) && (counter < mines->active_blocks); i++)
        {
            if (BlockIsActive(mine_cursor, mines)) 
            {
                DrawSphere(mine_cursor->position, mine_cursor->size, RED);
                counter++;
            }
            mine_cursor++;
        }
    }
    
}

void CheckMineTimers(MemoryPool_t *mines)
{
    if (mines->active_blocks > 0)
    {
        Mine_t* mine_cursor = (Mine_t*) mines->memory;
        LARGE_INTEGER t1, freq;
        for (int i = 0, counter = 0; (i < mines->pool_size) && (counter < mines->active_blocks); i++)
        {
            if (BlockIsActive(mine_cursor, mines)) 
            {
                QueryPerformanceFrequency(&freq);
                QueryPerformanceCounter(&t1);
                if (mine_cursor->endTime <= t1.QuadPart/freq.QuadPart) DeleteMine(mines, mine_cursor);
            }
            mine_cursor++;
        }
    }
}
