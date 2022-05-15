#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocate memory for an entity and return a pointer to it
 *
 * @param name name of the entity
 * @param position position of the entity
 * @return pointer to the memory which stores the entity
 */
Entity *newEntity(char name[10], Point2D_d position, Point2D_d size){
  Entity *e = NULL;
  e = malloc(sizeof(Entity));
  if (!e) {
    fprintf(stderr, "Memory allocation failed");
    exit(1);
  };
  strcpy(e->name, name);
  e->position = position;
  e->size = size;
  return e;
}

/**
 * @brief Print information about an entity to stdout
 *
 * @param entity Entity to print information about
 */
void printEntity(const Entity *entity){
  if (entity == NULL) {
    printf("NULL entity\n");
  } else {
    printf("Entity \"%s\" at %lf %lf\n", entity->name, entity->position.x, entity->position.y);
  }
}

void drawEntity(SDL_Renderer * renderer, Entity * entity) {
  SDL_Rect rect = {
    .x = entity->position.x,
    .y = entity->position.y,
    .w = entity->size.x,
    .h = entity->size.y,
  };
  SDL_SetRenderDrawColor(renderer, 255, 100, 100, 100);
  SDL_RenderFillRect(renderer, &rect);
}

/**
 * @brief Add an entity to an entitylist
 *
 * @param entityList EntityList to which an entity should be appended
 * @param e Entity to append
 */
void addEntity(EntityList * entityList, Entity * e) {
  if (entityList->entity==NULL) {
    printf("Es existiert bisher noch kein Element in dieser Liste\n");
    entityList->entity = e;
  } else {
    printf("! Es existiert bereits ein Element in dieser Liste\n");
    entityList->next = malloc(sizeof(EntityList));
    if (!entityList->next) {
      fprintf(stderr, "Memory allocation failed!");
      exit(1);
    }
    entityList->next->entity = e;
  }
}

/**
 * @brief Free all the memory allocated for an EntityList-
 *
 * @param entityList The EntityList which is supposed to be cleared
 */
void clearEntityList(EntityList *entityList){
  forEachEntity(entityList, free);
}

/**
 * @brief Execute a function f(x) for each entity x in a given entitylist
 *
 * @param entityList The entitylist to iterate over
 * @param f The function which should be executed with an entity as
 * an argument for each entity
 */
void forEachEntity(EntityList * entityList, void (*f)()){
  EntityList *el = entityList;
  f(el->entity);
  if (el->next) {
    el = el->next;
    f(el->entity);
  }
}

/**
 * @brief Calculate the number of elements in an entitylist
 *
 * @param entityList The entitylist for which the length should be calculated
 * @return The length of the entitylist
 */
int amountOfEntities(EntityList * entityList){
  printf("test\n");
  int i=0;
  EntityList* el = entityList;
  while (el) {
    i++;
    el = el->next;
  }
  return i;
};
