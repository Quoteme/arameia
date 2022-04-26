#ifndef GAME
#define GAME

typedef enum {
  RUNNING,
  PAUSED,
  CLOSING
} GameState;

typedef struct {
  GameState gamestate;
} Game;

#endif // !GAME
// vim: tabstop=2 shiftwidth=2 expandtab
