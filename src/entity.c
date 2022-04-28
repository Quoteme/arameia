#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>

void drawEntity(SDL_Renderer * renderer, Entity * entity) {
  SDL_Rect rect = {
    .x = entity->position.x,
    .y = entity->position.y,
    .w = entity->size.x,
    .h = entity->size.y,
  };
}
