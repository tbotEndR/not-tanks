#ifndef TANKS_H
#define TANKS_H
#include "raylib.h"

typedef struct Tank_t {
    Vector3 position;
    Vector3 bodyDirection;
    Vector3 turretDirection;
    float speed;
    int magsize;
} Tank_t;


Tank_t *TankCtor(Vector3 pos, Vector3 bodyDir, float speed);
void TankDtor(Tank_t *t);

#endif