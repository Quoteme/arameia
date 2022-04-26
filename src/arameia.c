#include <stdio.h>
#include <SDL2/SDL.h>

#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_video.h"
#include "game.h"
#include "entity.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer;
SDL_Event event;
int width = 640;
int height = 480;
Game game = {
  .gamestate = RUNNING
};

void InitSetup() {
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer);
  if (!window) {
    printf("InitSetup failed to create window");
  }
}

void GameLoop() {
  while (game.gamestate == RUNNING) {
    printf("Running...\n");
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
  InitSetup();
  GameLoop();
  FinishOff();
  printf("hallo welt");
  return 0;
}
// vim: tabstop=2 shiftwidth=2 expandtab
