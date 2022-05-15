#ifndef LEVEL_H

#include "entity.h"

typedef enum {
  AIR,
  GRASS,
  GRASS_UP_LEFT,
  GRASS_UP_RIGHT,
  STONE,
  STONE_UP_LEFT,
  STONE_UP_RIGHT
} Tile;

struct Level {
  char *name;
  EntityList *entities;
  Tile* tilegrid;
  int width;
  int height;
};

Tile* newTileGrid(int, int);

void printTileGrid(Tile*, int, int);

#endif // !LEVEL_H
// vim: tabstop=2 shiftwidth=2 expandtab
