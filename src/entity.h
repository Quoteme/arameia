/**
 * @file
 * @brief Data structure for an entity in game. This includes the player
 * enemies and all moveable objects
 */

#ifndef ENTITY
#define ENTITY

#include "animation.h"
#include "point.h"
#include "direction.h"
#include <SDL2/SDL.h>

typedef struct {
  int full, now;
} Health;

Health parseHealth(char *line);

typedef struct {
  Point2D_d position;
  Point2D_d size;
  Point2D_d velocity;
  Direction2D direction;
  Health health;
  char *name;
  AnimationSheet *animationSheet;
} Entity;

Entity *newEntity(char*);
void removeEntity(Entity*);
Entity *parseEntity(FILE*);
void addAnimationSheetToEntity(AnimationSheet*, Entity*);

void printEntity(const Entity*);

void drawEntity(SDL_Renderer*, Entity*);

typedef struct EntityList EntityList;
struct EntityList {
  Entity* entity;
  EntityList* next;
};

EntityList *newEntityList();
void addEntity(EntityList*, Entity*);
/* EntityList mapEntity(EntityList* , Entity (*f)); */
void forEachEntity(EntityList* , void (*f)());
int amountOfEntities(EntityList*);

void clearEntityList(EntityList *);

#endif // !ENTITY
// vim: tabstop=2 shiftwidth=2 expandtab ft=c
