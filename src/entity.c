#include "entity.h"
#include "direction.h"
#include "point.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
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
Entity *newEntity(char *name) {
  Entity *e = NULL;
  e = malloc(sizeof(Entity));
  if (!e) {
    fprintf(stderr, "Memory allocation failed");
    fprintf(stderr, "Could not allocate memory for entity %s", name);
    exit(1);
  };
  e->name = malloc(strlen(name));
  if (!e->name) {
    fprintf(stderr, "Memory allocation failed!\n");
    fprintf(stderr, "Could not allocate memory for entity name %s!\n", name);
  }
  strcpy(e->name, name);
  return e;
}

/**
 * @brief Clear the memory allocated for an entity
 *
 * @param e The entity which should be removed
 */
void removeEntity(Entity *e) {
  free(e->name);
  free(e);
}

/**
 * @brief Parse health given a line. This is used in parseEntity, to
 * parse an entities health. A line has the pattern:
 * ```
 * 100 98
 * ```
 * This would yield: (Health) {.full = 100, .now = 98};
 *
 * @param line Line containing health information
 * @return Health that was parsed from the input line
 */
Health parseHealth(char *line){
  Point2D_i p = parsePoint2D_i(line);
  Health h = (Health) {
    .full = p.x,
    .now = p.y
  };
  return h;
}

/**
 * @brief Given a line which stores an entity (like in a level file,
 * loaded by `loadLevel`), allocate memory for the described
 * entity and fill this memory with the fitting values.
 * Example line:
 * ## entity_name
 * POS: posX posY
 * DIM: sizeX sizeY
 * VEL: velocityX velocityY
 * DIR: direction2D
 * HEL: healthFull healthNow
 * ANI: animationSheetURL
 * ~
 *
 * @param fp File pointer to a file where an entity needs to be parsed.
 * Which entity gets parsed is determined by the stream position, whic
 * can be read by `fgetpos`.
 * @return The first entity that can be read in the file pointed to
 * by the parameter `fp` after the current stream position.
 * If no entity can be read, a NULL pointer will be returned.
 */
Entity *parseEntity(FILE *fp) {
  Entity *e;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char firstThreeChars[3];
  read = getline(&line, &len, fp);
  memcmp(firstThreeChars, line, 3);
  if (line[0]==']' || !strcmp(firstThreeChars, "## ")){
    return e;
  }else{
    e = newEntity(line + 3);
    e->name[strlen(e->name)-1] = '\0';
  }
  while ((read = getline(&line, &len, fp)) != -1) {
    if (line[0] == '~')
      break;
    memcpy(firstThreeChars, line, 3);
    line[strlen(line)-1] = '\0';
    if (strcmp(firstThreeChars, "POS")==0) {
      e->position = parsePoint2D_d(line+5);
    } else if (strcmp(firstThreeChars, "DIM")==0) {
      e->size = parsePoint2D_d(line+5);
    } else if (strcmp(firstThreeChars, "VEL")==0) {
      e->velocity = parsePoint2D_d(line+5);
    } else if (strcmp(firstThreeChars, "DIR")==0) {
      e->direction = parseDirection2D(line+5);
    } else if (strcmp(firstThreeChars, "HEL")==0) {
      e->health = parseHealth(line+5);
    } else if (strcmp(firstThreeChars, "ANI")==0) {
      e->animationSheet = loadAnimationSheet(line+5);
    }
  }
  return e;
};

/**
 * @brief AnimationSheets are not automatically included, when a newEntity
 * is called. This needs to be executed after calling `newEntity`
 * for the entity to have an AnimationSheet
 *
 * @param as AnimationSheet
 * @param e Entity
 */
void addAnimationSheetToEntity(AnimationSheet *as, Entity *e) {
  e->animationSheet = as;
};

/**
 * @brief Print information about an entity to stdout
 *
 * @param entity Entity to print information about
 */
void printEntity(const Entity *entity) {
  if (entity == NULL) {
    printf("NULL entity\n");
  } else {
    printf("Entity \"%s\" at %lf %lf\n", entity->name, entity->position.x,
           entity->position.y);
  }
}

void drawEntity(SDL_Renderer *renderer, Entity *entity) {
  SDL_Rect destination = {
      .x = entity->position.x,
      .y = entity->position.y,
      .w = entity->size.x,
      .h = entity->size.y,
  };
  // TODO: make this draw an image
  Animation* a = getAnimation(entity->animationSheet, "run_right");
  // FIX: This results in {x = 640, y = 480, w = 655745792, h = 91118759}. But why?
  /* SDL_Rect src = a->currentFrame->source; */
  SDL_Rect src = {0,0,32,32};
  SDL_RenderCopy(
    renderer,
    SDL_CreateTextureFromSurface(renderer,entity->animationSheet->spritesheet),
    &src,
    &destination);
}

/**
 * @brief Create a new entitylist
 *
 * @return Pointer to an entitylist
 */
EntityList *newEntityList() {
  EntityList *el = malloc(sizeof(EntityList));

  if (!el) {
    fprintf(stderr, "Memory allocation failed!\n");
    fprintf(stderr, "Could not allocate a new EntityList!\n");
    exit(1);
  }
  return el;
}

/**
 * @brief Add an entity to an entitylist
 *
 * @param entityList EntityList to which an entity should be appended
 * @param e Entity to append
 */
void addEntity(EntityList *entityList, Entity *e) {
  if (!entityList->entity) {
    entityList->entity = e;
  } else {
    EntityList *el = entityList;
    while (el->next) {
      el = el->next;
    }
    el->next = newEntityList();
    el->next->entity = e;
  }
}

/**
 * @brief Free all the memory allocated for an EntityList-
 *
 * @param entityList The EntityList which is supposed to be cleared
 */
void clearEntityList(EntityList *entityList) {
  forEachEntity(entityList, removeEntity);
}

/**
 * @brief Execute a function f(x) for each entity x in a given entitylist
 *
 * @param entityList The entitylist to iterate over
 * @param f The function which should be executed with an entity as
 * an argument for each entity
 */
void forEachEntity(EntityList *entityList, void (*f)()) {
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
int amountOfEntities(EntityList *entityList) {
  printf("test\n");
  int i = 0;
  EntityList *el = entityList;
  while (el) {
    i++;
    el = el->next;
  }
  return i;
};
