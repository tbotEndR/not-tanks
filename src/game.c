#include "game.h"

//  read level data from somewhere and initialize accordingly, for now hardcoded
Game_t *LevelInit()
{
    Game_t *newGame = (Game_t*) malloc(sizeof(Game_t));
    newGame->tanks = TankPoolCtor(5);
    newGame->projectiles = ProjectilePoolCtor(50);
    newGame->arena = ArenaCtor(78, 50, 2.0f);
    return newGame;
}

void LevelStop(Game_t *g)
{
    TankPoolDtor(g->tanks);
    ProjectilePoolDtor(g->projectiles);
    ArenaDtor(g->arena);
    free(g);
}
