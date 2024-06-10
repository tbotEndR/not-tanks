#ifndef ARENA_H
#define ARENA_H
#define CELLSIZE 2
#include "raylib.h"

enum Celltype {EMPTY, WALL_SOLID, WALL_DEST, HOLE};

typedef struct Cell{
    Vector3 centerCoords; 
    enum Celltype type;
}Cell;

typedef struct Arena{
    int width;          // playable area
    int depth;          // playable area
    float cellsize;
    Cell **grid;
}Arena;

Arena *ArenaCtor(int w, int d, float cellsize); // initializes an empty arena with only walls
void ArenaDtor(Arena *arena);
void DrawArena(Arena *arena);

#endif