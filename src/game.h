#ifndef GAME
#define GAME

#include "entity.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>

typedef enum {
  RUNNING,
  PAUSED,
  CLOSING
} GameState;

typedef struct {
  GameState gamestate;
  EntityList entityList;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event *event;

} Game;

#endif // !GAME
// vim: tabstop=2 shiftwidth=2 expandtab
