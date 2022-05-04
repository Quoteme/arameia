#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Entity *newEntity(char name[10], Point2D position){
  Entity *e = NULL;
  e = malloc(sizeof(Entity));
  strcpy(e->name, name);
  e->position = position;
  return e;
}

void printEntity(const Entity *entity){
  if (entity == NULL) {
    printf("NULL entity\n");
  } else {
    printf("Entity at %lf %lf\n", entity->position.x, entity->position.y);
  }
}

void drawEntity(SDL_Renderer * renderer, Entity * entity) {
  SDL_Rect rect = {
    .x = entity->position.x,
    .y = entity->position.y,
    .w = entity->size.x,
    .h = entity->size.y,
  };
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
  SDL_RenderFillRect(renderer, &rect);
}

void addEntity(EntityList * entityList, Entity * e) {
  if (entityList->entity==NULL) {
    printf("Es existiert bisher noch kein Element in dieser Liste\n");
    entityList->entity = e;
  } else {
    printf("! Es existiert bereits ein Element in dieser Liste\n");
    entityList->next = malloc(sizeof(EntityList));
    entityList->next->entity = e;
  }
}

void forEachEntity(EntityList * entityList, void (*f)()){
  f(entityList->entity);
  if (entityList->next != NULL) {
    forEachEntity(entityList->next, *f);
  }
}

int amountOfEntities(EntityList * entityList){
  printf("test\n");
  int i=0;
  if (&(entityList->next)!=NULL) {
    entityList = entityList->next;
    i++;
  }
  if (&(entityList->next)!=NULL) {
    entityList = entityList->next;
    i++;
  }
  if (&(entityList->next)!=NULL) {
    entityList = entityList->next;
    i++;
  }
  if (&(entityList->next)!=NULL) {
    entityList = entityList->next;
    i++;
  }
  if (&(entityList->next)!=NULL) {
    entityList = entityList->next;
    i++;
  }
  /* while (&(entityList->next)!=NULL) { */
  /*   entityList = entityList->next; */
  /*   i++; */
  /* } */
  return i;
};
