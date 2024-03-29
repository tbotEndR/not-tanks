#include "arena.h"
#include <stdlib.h>

Arena *ArenaCtor(int w, int d, float cellsize)
{
    Arena* empty_arena = (Arena*) malloc(sizeof(Arena));
    empty_arena->depth = d/cellsize+1;
    empty_arena->width = w/cellsize+1;
    empty_arena->cellsize = cellsize;
    empty_arena->grid = (Cell**) malloc(sizeof(Cell[empty_arena->depth]));
    for (int i = 0; i < empty_arena->depth; i++)
    {
        empty_arena->grid[i] = (Cell*) malloc(sizeof(Cell[empty_arena->width]));
    }

    int z_offset, x_offset;
    for (int i = 0; i < empty_arena->depth; i++)
    {
        z_offset = i * cellsize;
        for (int j = 0; j < empty_arena->width; j++)
        {
            x_offset = j * cellsize;
            if ((i == 0) || (j == 0) || (j == empty_arena->width-1) || (i == empty_arena->depth-1))
            {
                empty_arena->grid[i][j].type = WALL_SOLID;
                empty_arena->grid[i][j].centerCoords = (Vector3) {(w/2 - x_offset), 1.0f, (d/2 - z_offset)};  // offset cell coordinates by array index
            }
        }
    }
    return empty_arena;
}

void ArenaDtor(Arena *arena)
{
    for (int i = 0; i < arena->depth; i++)
    {
        free(arena->grid[i]);
    }
    free(arena->grid);
    free(arena);
}


void DrawArena(Arena *arena)
{
    if (arena)
    {
        for (int i = 0; i < arena->depth; i++)
        {
            for (int f = 0; f < arena->width; f++)
            {
                switch(arena->grid[i][f].type)
                {
                    case WALL_SOLID:
                        DrawCube(arena->grid[i][f].centerCoords, arena->cellsize, arena->cellsize, arena->cellsize, BEIGE);
                        DrawCubeWires(arena->grid[i][f].centerCoords, arena->cellsize, arena->cellsize, arena->cellsize, DARKGRAY);
                        break;
                    case WALL_DEST:
                        DrawCube(arena->grid[i][f].centerCoords, arena->cellsize, arena->cellsize, arena->cellsize, BROWN);
                        DrawCubeWires(arena->grid[i][f].centerCoords, arena->cellsize, arena->cellsize, arena->cellsize, DARKGRAY);
                        break;
                    case HOLE:
                        DrawCircle3D(arena->grid[i][f].centerCoords, 2.0f, (Vector3){0.0f,0.0f,1.0f}, 0.0f, BLACK);   
                        break;
                    default:              
                }
            }
        }
    }
}