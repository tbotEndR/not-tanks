#ifndef TANKS_H
#define TANKS_H
#include <raylib.h>

typedef struct Tank_t {
    Vector3 position;
    Vector3 bodyDirection;
    Vector3 turretDirection;
    float speed;
    int magsize;
} Tank_t;

typedef struct TankPool {
    int size;
    int actives;
    Tank_t *tanks;
} TankPool;

Tank_t *TankCtor(Vector3 pos, Vector3 bodyDir, float speed);
TankPool *TankPoolCtor(int size);
void TankDtor(Tank_t *t);
void TankPoolDtor(TankPool *tp);

#endif