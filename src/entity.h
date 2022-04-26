#ifndef ENTITY
#define ENTITY

#include "health.h"
#include "point.h"
#include "direction.h"

typedef struct {
  Point2D position;
  Point2D velocity;
  Direction2D direction;
  Health health;
} Entity;

#endif // !ENTITY
// vim: tabstop=2 shiftwidth=2 expandtab
