#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "structures.h"

void init_board(Player *player1, Player *player2);

void propagate(point *p, Player *player, char color, bool *change);
void bad_update_board(Player *player, char color);

void update_board_bfs(point *p, bool *seen, queue *q, Player *player, char color);
void update_board(Player *player, char color);

#endif
