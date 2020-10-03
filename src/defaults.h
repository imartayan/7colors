#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "structures.h"

#define NB_COLORS 7

#define BOARD_SIZE 10
#define SCORE_MAX (BOARD_SIZE * BOARD_SIZE)

#define PLAYER1 '1'
#define PLAYER2 '2'

extern const char colors[];
extern char board[BOARD_SIZE * BOARD_SIZE];
extern const point direction[];
extern point start1, start2;

#endif