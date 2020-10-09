#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "structures.h"

const point direction[4];

void init_board(State *state);

void propagate(point *p, State *state, char color, bool *change);
void bad_update_board(State *state, char color);

void update_board_bfs(point *p, bool *seen, queue *q, State *state, char color);
void update_board(State *state, char color);

#endif
