#include "level.h"
#include "entity.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      printf("%d", tg[x + width * y]);
    }
    printf("\n");
  }
  /* for (Tile *t = tg; t < tg + width * height; t++) { */
  /*   printf("%d", *t); */
  /*   if ((t - tg) % width == 0) */
  /*     printf("\n"); */
  /* } */
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
  if (!file) {
    fprintf(stderr, "File not found error");
    exit(1);
  };
  // parse line by line
  char *line;
  size_t linelength = 0;
  // the first line contains the ⭐ name ⭐
  if (getline(&line, &linelength, file) != -1) {
    l->name = malloc(linelength * sizeof(char));
    if (!l->name) {
      fprintf(stderr, "Memory allocation failed!\n");
      exit(1);
    }
    strncpy(l->name, line, linelength * sizeof(char));
    l->name[strlen(l->name)-1] = '\0';
  }
  // the next lines form a block delimited by `[` and `]` like this:
  // [
  // ...
  // ]
  // and this block stores all the ⭐ entities ⭐, each in one line.
  if (getline(&line, &linelength, file) != -1) {
    if (strcmp(line, "[")) {
      printf("starting parse of stored entities\n");
    }
  }
  l->entities = newEntityList();
  Entity *parsedEntity;
  while (true) {
    parsedEntity = parseEntity(file);
    if (!parsedEntity)
      break;
    else
      addEntity(l->entities, parsedEntity);
  }
  // Get ⭐ height ⭐ of the stored tilegrid
  fpos_t locationWhereTheTilegridStarts;
  l->height = 0;
  fgetpos(file, &locationWhereTheTilegridStarts);
  while (getline(&line, &linelength, file) != -1) {
    l->height++;
  }
  fsetpos(file, &locationWhereTheTilegridStarts);
  // Get ⭐ width ⭐ of the stored tilegrid
  l->width = 0;
  for (char c = *line; c; c = *line++) {
    if (c == ',')
      l->width++;
  }
  // parse ⭐ tilegrid ⭐
  // store each character in an array of length 8 and when a `,` appears
  // convert this array to an integer, add the value to the tilegrid
  // and flush the array. Repeat until all values in the file have
  // been parsed
  l->tilegrid = newTileGrid(l->width, l->height);
  int tilegridIndex = 0;
  int charactersSinceLastComma = 0;
  char commaDelimitedCharacterSequence[8];
  while (getline(&line, &linelength, file) != -1) {
    for (int i = 0; i < strlen(line); i++) {
      if (line[i] != ',') {
        commaDelimitedCharacterSequence[charactersSinceLastComma] = line[i];
        charactersSinceLastComma++;
      } else {
        l->tilegrid[tilegridIndex] = atoi(commaDelimitedCharacterSequence);
        tilegridIndex++;
        charactersSinceLastComma = 0;
        memset(commaDelimitedCharacterSequence, 0,
               sizeof(commaDelimitedCharacterSequence));
      }
    }
  }

  fclose(file);
  return l;
}

//TODO: add a method to clear a level from memory

void printLevel(Level *l) {
  printf("Level: %s\n", l->name);
  printf("Entities:[\n");
  forEachEntity(l->entities, printEntity);
  printf("]\n");
  printf("width: %d, height: %d\n", l->width, l->height);
  printTileGrid(l->tilegrid, l->width, l->height);
}
