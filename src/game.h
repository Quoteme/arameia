/**
 * @file
 * @brief data structures that for resuming, pausing ans storing
 * information about the game
 */

#ifndef GAME
#define GAME

#include "level.h"
#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef enum { RUNNING, PAUSED, CLOSING } GameState;

typedef struct {
  GameState gamestate;
  Level *level;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

} Game;

#endif // !GAME
// vim: tabstop=2 shiftwidth=2 expandtab
