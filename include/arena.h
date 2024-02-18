#ifndef ARENA_H
#define ARENA_H

enum Celltype { EMPTY, WALL_SOLID, WALL_DEST, HOLE};

typedef struct Cell{
    double size;        // cells are cubes
    double xCoord;      // coordinates of the top left corner of a cell
    double yCoord;  
    enum Celltype type;
}Cell;

typedef struct Arena{
    int width;          // playable area
    int depth;          // playable area
    Cell **grid;
}Arena;

#endif