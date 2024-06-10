#include "level.h"

//  read level data from somewhere and initialize accordingly, for now hardcoded
Level_t *LevelInit()
{
    Level_t *newGame = (Level_t*) malloc(sizeof(Level_t));
    //newGame->tanks = AllocPool(sizeof(Tank_t), 5);
    newGame->projectiles = AllocateMemoryPool(sizeof(Projectile_t), 100);
    newGame->mines = AllocateMemoryPool(sizeof(Mine_t), 25);
    newGame->arena = ArenaCtor(78, 50, 2.0f);
    return newGame;
}

void LevelStop(Level_t *g)
{
    ArenaDtor(g->arena);
    DeallocateMemoryPool(g->mines);
    //FreePool(g->tanks);
    DeallocateMemoryPool(g->projectiles);
    free(g);
}
