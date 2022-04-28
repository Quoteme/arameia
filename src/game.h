#ifndef GAME
#define GAME

#include "entity.h"

typedef enum {
  RUNNING,
  PAUSED,
  CLOSING
} GameState;

typedef struct {
  GameState gamestate;
  EntityList entityList;
} Game;

#endif // !GAME
// vim: tabstop=2 shiftwidth=2 expandtab
