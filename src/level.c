#include "level.h"

//  read level data from somewhere and initialize accordingly, for now hardcoded
Level_t *LevelInit()
{
    Level_t *newGame = (Level_t*) malloc(sizeof(Level_t));
    newGame->tanks = AllocPool(sizeof(Tank_t), 5);
    newGame->projectiles = AllocPool(sizeof(Projectile_t), 100);
    newGame->mines = AllocPool(sizeof(Mine_t), 25);
    newGame->arena = ArenaCtor(78, 50, 2.0f);
    return newGame;
}

void LevelStop(Level_t *g)
{
    ArenaDtor(g->arena);
    FreePool(g->mines);
    FreePool(g->tanks);
    FreePool(g->projectiles);
    free(g);
}

Qtree_t *CreateQuadTree(Level_t *level)
{
    Qtree_t *newQuadTree = (Qtree_t*) malloc(sizeof(Qtree_t));
    return NULL;
}

void UpdateQuadTree(Qtree_t *qtree)
{

}

void DeleteQuadTree(Qtree_t *qtree)
{

}
