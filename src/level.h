#pragma once

#include <stdbool.h>

#define MAP_SIZE 128

typedef struct {
    int top, left, bottom, right;
} Rect;

typedef struct {
    int color;
    bool visible;
    bool solid;
    char ch;
} Tile;

typedef struct {
    Tile tiles[MAP_SIZE][MAP_SIZE];
} Level;

void genOverworld(Level *level);
void genCave(Level *level);

void renderLevel(Level *level, Rect viewport);

Tile getTile(Level *level, int row, int col);
void setTile(Level *level, int row, int col, Tile *tile);
bool inBounds(int row, int col);
