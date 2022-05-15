#include <SDL2/SDL.h>
#include <stdio.h>

#include "direction.h"
#include "entity.h"
#include "game.h"
#include "level.h"
#include "point.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

int width = 640;
int height = 480;
Game game = {
    .gamestate = RUNNING,
};

void InitSetup(Game *game) {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &game->window,
                              &game->renderer);
  if (!game->window) {
    printf("InitSetup failed to create window");
  }
}

/**
 * @brief This function is added so it can be passed to `forEachEntity`
 * during the GameLoop allowing much easier drawing, movement, etc. of
 * entities.
 *
 * @param entity The entity that should be drawn
 */
void updateEntity(Entity *entity) { drawEntity(game.renderer, entity); }

/**
 * @brief Main game loop. Responsible for drawing, handling input, etc.
 *
 * @param game The game instance which will be used
 */
void GameLoop(Game *game) {
  SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 100);
  while (game->gamestate == RUNNING) {
    /* forEachEntity(&game->entityList, updateEntity); */
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

int main(int argc, char *argv[]) {
  Entity *player = newEntity("player    ", (Point2D_d){.x = 0.0, .y = 0.0},
                             (Point2D_d){.x = 16.0, .y = 16.0});
  Entity *enemy = newEntity("enemy     ", (Point2D_d){.x = 100.0, .y = 100.0},
                            (Point2D_d){.x = 16.0, .y = 16.0});
  /* addEntity(&game.entityList, player); */
  /* addEntity(&game.entityList, enemy); */
  /* forEachEntity(&game.entityList, printEntity); */
  /* InitSetup(&game); */
  /* GameLoop(&game); */
  /* FinishOff(&game); */
  /* clearEntityList(&game.entityList); */
  char *levelName = "lvl/aNewHorizon.csv";
  game.level = loadLevel(levelName);
  printLevel(game.level);
  return 0;
}
// vim: tabstop=2 shiftwidth=2 expandtab
