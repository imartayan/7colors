/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Header file of the board module */

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include "defaults.h"

/** Retrieves the color of a given board cell */
char get_cell(int x, int y);

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color);

bool in_bounds(int x, int y);

int randint(int n);

char random_color();
char play_random_color(char player);

int color_id(char c);

int count_true(bool *tab, int len);
int get_nth_true(bool *tab, int len, int n);

#endif
