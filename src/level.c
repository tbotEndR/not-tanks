#include "level.h"

//  read level data from somewhere and initialize accordingly, for now hardcoded
Level_t *LevelInit()
{
    Level_t *newGame = (Level_t*) malloc(sizeof(Level_t));
    newGame->tanks = TankPoolCtor(5);
    newGame->projectiles = ProjectilePoolCtor(50);
    newGame->mines = MinePoolCtor(10);
    newGame->arena = ArenaCtor(78, 50, 2.0f);
    return newGame;
}

void LevelStop(Level_t *g)
{
    TankPoolDtor(g->tanks);
    ProjectilePoolDtor(g->projectiles);
    ArenaDtor(g->arena);
    free(g);
}
