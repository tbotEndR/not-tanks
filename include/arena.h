#ifndef ARENA_H
#define ARENA_H
#include <raylib.h>

enum Celltype {EMPTY, WALL_SOLID, WALL_DEST, HOLE};

typedef struct Cell{
    double size;        // cells are cubes
    Vector3 centerCoords; 
    enum Celltype type;
}Cell;

typedef struct Arena{
    int width;          // playable area
    int depth;          // playable area
    Cell **grid;
}Arena;

Arena *ArenaCtor(int w, int d); // initializes an empty arena with only walls
void DrawArena(Arena *arena);

#endif