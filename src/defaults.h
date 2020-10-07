#ifndef DEFAULTS_H
#define DEFAULTS_H

#include "structures.h"

#define NB_COLORS 7

#define BOARD_SIZE 30
#define SCORE_MAX (BOARD_SIZE * BOARD_SIZE)
#define NB_CASES (BOARD_SIZE * BOARD_SIZE)

#define PLAYER1 '1'
#define PLAYER2 '2'

const char colors[NB_COLORS];
const point direction[4];
point start1, start2;

#endif
