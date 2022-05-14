#include <stdio.h>
#include <SDL2/SDL.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include "direction.h"
#include "game.h"
#include "entity.h"
#include "point.h"

int width = 640;
int height = 480;
Game game = {
  .gamestate = RUNNING,
  .entityList = (EntityList) {}
};

void InitSetup(Game *game) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &game->window, &game->renderer);
  if (!game->window) {
    printf("InitSetup failed to create window");
  }
}

void GameLoop(Game *game) {
  SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 100);
  while (game->gamestate == RUNNING) {
    /* printf("Running...\n"); */
    SDL_RenderPresent(game->renderer);
    while (SDL_PollEvent(&game->event)) {
      if (game->event.type == SDL_KEYDOWN) {
        game->gamestate = CLOSING;
        break;
      }
    }
  }
}

void FinishOff(Game *game) {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  exit(0);
}

int main (int argc, char *argv[]) {
  Entity *player = newEntity("player    ", (Point2D_d) {.x=0.0, .y=0.0});
  Entity *enemy = newEntity("enemy     ", (Point2D_d) {.x=2.0, .y=0.0});
  addEntity(&game.entityList, player);
  addEntity(&game.entityList, enemy);
  forEachEntity(&game.entityList, printEntity);
  InitSetup(&game);
  GameLoop(&game);
  FinishOff(&game);
  return 0;
}
// vim: tabstop=2 shiftwidth=2 expandtab
