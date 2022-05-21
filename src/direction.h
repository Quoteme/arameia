/**
 * @file
 * @brief Simple data structure for all possible directions an entity
 * may look
 */

#ifndef DIRECTION
#define DIRECTION

typedef enum { UP, DOWN, LEFT, RIGHT } Direction2D;

Direction2D parseDirection2D(char *line);

#endif // !DIRECTION
// vim: tabstop=2 shiftwidth=2 expandtab
