#ifndef COLLISION_H
#define COLLISION_H
#include "level.h"

typedef struct Qtree_t {
    struct Qtree_t *northEast, *southEast, *southWest, *northWest;     //  +x+y, +x-y, -x-y, -x+y
    void *entityPool;
} Qtree_t;

Qtree_t *CreateQuadTree(Level_t *level);
void UpdateQuadTree(Qtree_t *qtree);
void DeleteQuadTree(Qtree_t *qtree);

#endif