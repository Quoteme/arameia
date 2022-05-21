#ifndef POINT
#define POINT

#include <stdio.h>

typedef struct {
  double x, y;
} Point2D_d;

typedef struct {
  int x, y;
} Point2D_i;

Point2D_d parsePoint2D_d(char *);
Point2D_i parsePoint2D_i(char *);

#endif // !POINT
// vim: tabstop=2 shiftwidth=2 expandtab
