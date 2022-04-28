#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>

void drawEntity(SDL_Renderer * renderer, Entity * entity) {
  SDL_Rect rect = {
    .x = entity->position.x,
    .y = entity->position.y,
    .w = entity->size.x,
    .h = entity->size.y,
  };
  printf("lall");
}

void addEntity(EntityList * entityList, Entity e) {
  if (&(entityList->entity)==NULL) {
    printf("Es existiert bisher noch kein Element in dieser Liste\n");
    entityList->entity = e;
  } else {
    printf("! Es existiert bereits ein Element in dieser Liste\n");
    /* entityList->next = &(EntityList) {.entity = e}; */
  }
}

void forEachEntity(EntityList * entityList, void (*f)()){
  f(entityList->entity);
  if (entityList->next != NULL) {
    forEachEntity(entityList->next, *f);
  }
}

int amountOfEntities(EntityList * entityList, int accumulator){
  if (entityList->next!=NULL) {
    return amountOfEntities(entityList, accumulator+1);
  } else {
    return accumulator;
  }
};
