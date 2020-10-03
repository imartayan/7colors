/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Header file of the board module */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include "defaults.h"

/** Retrieves the color of a given board cell */
char get_cell(int x, int y);

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color);

int randint(int n);
char random_color();

#endif
