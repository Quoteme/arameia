#include "Level.h"
#include <stdio.h>

Tile* newTileGrid(int width, int height){
  Tile *tg = calloc(width*height, sizeof(Tile));

  if (!tg) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(1);
  }
  
  return tg;
}

void printTileGrid(Tile *tg, int width, int height){
  for (Tile* t = tg; t < tg+width*height; t++) {
    printf("%d", *t);
    if ((t-tg)%width==0) printf("\n");
  }
}
