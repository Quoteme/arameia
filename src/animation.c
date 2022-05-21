#include "animation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_image.h>

#define VALUESPERFRAME 5
#define MAXDIGITLENGTH 5

/**
 * @brief Get the number of animations stored in a file, which stores
 * an AnimationSheet
 *
 * @param file A file, which stores an AnimationSheet
 * @return Number of animations in a file storing an AnimationSheet
 */
int getNumberOfAnimationsInAnimationSheetFile(FILE *file) {
  int numOfAnimations = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  fpos_t tmp;
  fgetpos(file, &tmp);
  while ((read = getline(&line, &len, file)) != -1) {
    if (read > 0 && line[0] == '#')
      numOfAnimations++;
  }
  fsetpos(file, &tmp);
  return numOfAnimations;
}

Frame *loadFrame(char *line) {
  Frame *f = malloc(sizeof(Frame));
  if (!f) {
    fprintf(stderr, "Memory allocation failed!\n");
    fprintf(stderr, "Could not allocate memory for a new frame!\n");
    exit(1);
  }
  int parsedValues[VALUESPERFRAME];
  int valueToParse = 0;
  char digit[MAXDIGITLENGTH];
  int digitInput = 0;
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] == ' ') {
      // this gets fired when a value has be completely parsed
      /* parsedValues[valueToParse] = atoi(digit); */
      valueToParse++;
      if (valueToParse >= VALUESPERFRAME)
        break;
      digitInput = 0;
      for (int j = 0; j < MAXDIGITLENGTH; j++) {
        digit[j] = ' ';
      }
    } else {
      digit[digitInput] = line[i];
      digitInput++;
    }
  }
  /* f->source = (SDL_Rect){.x = parsedValues[0], */
  /*                        .y = parsedValues[1], */
  /*                        .w = parsedValues[2], */
  /*                        .h = parsedValues[3]}; */
  /* f->duration = parsedValues[4]; */
  return f;
}

void addFrame(Animation a, Frame *f) {
  if (!a.currentFrame) {
    a.currentFrame = f;
  } else {
    Frame *cf = a.currentFrame;
    while (cf->next) {
      cf = cf->next;
    }
    // reached the last frame, which does not have a `next` frame in
    // the animation
    cf->next = f;
  }
}

/**
 * @brief Load an animation from a file. This changes the file pointer.
 * This function is called from `loadAnimationSheet` when the
 * animation block of an AnimationSheet file starts.
 * This will parse the file until a new animation starts.
 * An animationblock has the form:
 * ```
 * # animation_name
 * frameStartX frameStartY frameEndX frameEndY
 * frame2StartX frame2StartY frame2EndX frame2EndY
 * ~
 * ```
 *
 * @return Loaded animation
 */
Animation loadAnimation(FILE *file) {
  Animation a;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&line, &len, file)) != -1) {
    if (read > 0) {
      if (line[0] == '#') {
        a.name = malloc(strlen(line + 2) + 1);
        if (!a.name) {
          fprintf(stderr, "Memory allocation failed!\n");
          fprintf(stderr, "Could not allocate memory for animation name!\n");
          exit(1);
        }
        strcpy(a.name, line + 2);
        a.name[strlen(a.name) - 1] = '\0';
      } else if (line[0] == '~') {
        break;
      } else {
        addFrame(a, loadFrame(line));
      }
    }
  }
  return a;
}

AnimationSheet *loadAnimationSheet(char *url) {
  AnimationSheet *as = malloc(sizeof(AnimationSheet));
  if (!as) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(1);
  }

  FILE *file;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  file = fopen(url, "r");
  if (!file) {
    fprintf(stderr, "Animation file \"%s\" does not exist!\n", url);
    exit(1);
  }

  // parse image from here
  // TODO: load with SDL_image
  read = getline(&line, &len, file);
  line[strlen(line)-1] = '\0';
  printf("loading spritesheet from: %s\n", line);
  as->spritesheet = IMG_Load(line);

  // parse animations
  int numOfAnimations = getNumberOfAnimationsInAnimationSheetFile(file);
  printf("There are %d animations defined in file %s\n", numOfAnimations, url);

  as->animations = malloc(numOfAnimations * sizeof(Animation));

  if (!as->animations) {
    fprintf(stderr, "Memory allocation failed!\n");
    fprintf(stderr, "Could not allocate memory for animations\n");
    exit(1);
  }

  for (int i = 0; i < numOfAnimations; i++) {
    Animation a = loadAnimation(file);
    as->animations[i].name = a.name;
    as->animations[i].currentFrame = a.currentFrame;
  }

  return as;
}

// vim: tabstop=2 shiftwidth=2 expandtab ft=c
