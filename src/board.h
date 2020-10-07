#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "defaults.h"
#include "structures.h"
#include "utils.h"

void init_board(char* board);

void propagate(char* board, point *p, char player, char color, bool *change, int *score);
void bad_update_board(char* board, char player, char color, int *score);

void visit_bfs(pstate state, point *p, bool *seen, queue *visit);
void update_board_bfs(pstate state);

#endif
