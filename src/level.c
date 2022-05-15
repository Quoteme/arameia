#include "level.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Tile *newTileGrid(int width, int height) {
  Tile *tg = calloc(width * height, sizeof(Tile));

  if (!tg) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(1);
  }

  return tg;
}

void printTileGrid(Tile *tg, int width, int height) {
  for (Tile *t = tg; t < tg + width * height; t++) {
    printf("%d", *t);
    if ((t - tg) % width == 0)
      printf("\n");
  }
}

Level *loadLevel(char *path) {
  // allocate memory for a level
  printf("Loading level: %s\n", path);
  Level *l = malloc(sizeof(Level));
  if (!l) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(1);
  }

  // 🚀 level file parsing 🚀
  FILE *file = fopen(path, "r");
  if (!file){
    fprintf(stderr, "File not found error");
    exit(1);
  };
  // parse line by line
  char *line;
  size_t linelength = 0;
  // the first line contains the ⭐ name ⭐
  if (getline(&line, &linelength, file) != -1){
    printf("level name is: %s\n", line);
    l->name = malloc(linelength * sizeof(char));
    if (!l->name) {
      fprintf(stderr, "Memory allocation failed!\n");
      exit(1);
    }
    strncpy(l->name, line, linelength*sizeof(char));
  }
  // the next lines form a block delimited by `[` and `]` like this:
  // [
  // ...
  // ]
  // and this block stores all the ⭐ entities ⭐, each in one line.
  if (getline(&line, &linelength, file) != -1){
    if (strcmp(line, "[")) {
      printf("starting parse of stored entities\n");
    }
  }
  // TODO: parse entities stored
  if (getline(&line, &linelength, file) != -1){
    if (strcmp(line, "]")) {
      printf("ending parse of stored entities\n");
    }
  }

  fclose(file);

  return l;
}

void printLevel(Level *l){
  printf("Level: %s\n", l->name);
  printTileGrid(l->tilegrid, l->width, l->height);
}
