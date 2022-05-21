#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPOINTCHARLENGTH 8

/**
 * @brief Parse a point from a line
 * 
 * @param line The line which gets parsed 
 * @return Point2D_d 
 */
Point2D_d parsePoint2D_d(char *line){
  Point2D_d p;
  p.y = atof(strchr(line, ' '));
  *strchr(line, ' ') = '\0';
  p.x = atof(line);
  return p;
}

/**
 * @brief Parse a point from a line
 * 
 * @param line The line which gets parsed 
 * @return Point2D_i 
 */
Point2D_i parsePoint2D_i(char *line){
  Point2D_i p;
  p.y = atoi(strchr(line, ' '));
  *strchr(line, ' ') = '\0';
  p.x = atoi(line);
  return p;
}