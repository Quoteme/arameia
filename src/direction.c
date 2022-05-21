#include "direction.h"
#include <string.h>

Direction2D parseDirection2D(char *line) {
  if (strcmp(line, "UP"))
    return UP;
  else if (strcmp(line, "DOWN"))
    return DOWN;
  else if (strcmp(line, "LEFT"))
    return LEFT;
  else
    return RIGHT;
}
