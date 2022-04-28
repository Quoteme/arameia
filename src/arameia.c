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

SDL_Window* window = NULL;
SDL_Renderer* renderer;
SDL_Event event;
int width = 640;
int height = 480;
Game game = {
  .gamestate = RUNNING,
  .entityList = (EntityList) {}
};

void InitSetup() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer);
  if (!window) {
    printf("InitSetup failed to create window");
  }
}

void GameLoop() {
  SDL_Rect rect = {
    .x = 0,
    .y = 0,
    .w = 100,
    .h = 100
  };
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
  while (game.gamestate == RUNNING) {
    printf("Running...\n");
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        game.gamestate = CLOSING;
        break;
      }
    }
  }
}

void FinishOff() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  exit(0);
}

int main (int argc, char *argv[]) {
  Entity player = {
    .direction = (Direction2D) {RIGHT},
    .health = (Health) {
      .full = 1.0,
      .now = 1.0,
    },
    .position = (Point2D) {.x = 0.0, .y = 0.0},
    .size = (Point2D) {.x = 8.0, 8.0},
    .velocity = (Point2D) {.x = 0.0, .y = 0.0},
  };
  InitSetup();
  GameLoop();
  FinishOff();
  printf("hallo welt");
  return 0;
}
// vim: tabstop=2 shiftwidth=2 expandtab
