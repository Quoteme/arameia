#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

typedef struct {
  int duration;
  SDL_Rect source;
} Frame;

typedef struct {
  Frame *frames;
  SDL_Surface *spritesheet;
} Animation;

Animation *loadAnimation(char *);

#endif // !ANIMATION_H
#define ANIMATION_H
// vim: tabstop=2 shiftwidth=2 expandtab ft=c
