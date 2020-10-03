#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "defaults.h"
#include "structures.h"
#include "utils.h"

void init_board(char* board);

void propagate(char* board, point *p, char curr_player, char color, bool *change, int *score1, int *score2);
void bad_update_board(char* board, char curr_player, char color, int *score1, int *score2);

void visit_bfs(char* board, point *p, bool *seen, queue *q, char player, char color, int *score1, int *score2);
void update_board_bfs(char* board, char player, char color, int *score1, int *score2);

#endif
