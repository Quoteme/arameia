#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

typedef struct Frame Frame;
struct Frame{
  int duration;
  SDL_Rect source;
  Frame *next;
};

typedef struct {
  Frame *currentFrame;
  char *name;
} Animation;

typedef struct {
  Animation *animations;
  SDL_Surface *spritesheet;
} AnimationSheet;

SDL_Rect loadRect(char *);
Frame *loadFrame(char *);
void addFrame(Animation, Frame*);
Animation loadAnimation(FILE *);
AnimationSheet *loadAnimationSheet(char *);

int getNumberOfAnimationsInAnimationSheetFile(FILE *);

#endif // !ANIMATION_H
#define ANIMATION_H
// vim: tabstop=2 shiftwidth=2 expandtab ft=c
