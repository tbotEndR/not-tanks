#include "arena.h"

Arena *ArenaCtor(int w, int d)
{
    Arena *newArena = (Arena*) malloc(sizeof(Arena));
    newArena->depth = d+2;  // depth specifies playable area, add 2 for the borders
    newArena->width = w+2;  // width specifies playable area, add 2 for the borders
    newArena->grid = 
}

void DrawArena(Arena *arena)
{
    int width = arena->width;
    int depth = arena->depth;
    for (int i = 0; i < width; i++)
    {
        for (int f = 0; f < depth; f++)
        {
            switch(arena->grid[width][depth].type)
            {
                case WALL_SOLID:
                    DrawCube(arena->grid[width][depth].centerCoords, 2.0f, 2.0f, 2.0f, BEIGE);
                case WALL_DEST:
                    DrawCube(arena->grid[width][depth].centerCoords, 2.0f, 2.0f, 2.0f, BROWN);
                case HOLE:
                    DrawCircle3D(arena->grid[width][depth].centerCoords, 2.0f, (Vector3){0.0f,0.0f,1.0f}, 0.0f, BLACK);                 
            }
        }
    }
}

