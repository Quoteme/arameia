#ifndef ENTITY
#define ENTITY

#include "health.h"
#include "point.h"
#include "direction.h"
#include <SDL2/SDL.h>

typedef struct {
  Point2D position;
  Point2D size;
  Point2D velocity;
  Direction2D direction;
  Health health;
  char name[10];
} Entity;

Entity *newEntity(char[10], Point2D);

void printEntity(const Entity*);

void drawEntity(SDL_Renderer*, Entity*);

typedef struct EntityList EntityList;
struct EntityList {
  Entity* entity;
  EntityList* next;
};

void addEntity(EntityList*, Entity*);
/* EntityList mapEntity(EntityList* , Entity (*f)); */
void forEachEntity(EntityList* , void (*f)());
int amountOfEntities(EntityList*);

#endif // !ENTITY
// vim: tabstop=2 shiftwidth=2 expandtab ft=c
