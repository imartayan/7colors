#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "defaults.h"
#include "structures.h"
#include "utils.h"

void init_board();

void propagate(point *p, char player, char color, bool *change, int *score);
void bad_update_board(char player, char color, int *score);

void update_board_bfs(point *p, bool *seen, queue *q, char player, char color, int *score);
void update_board(char player, char color, int *score);

#endif
