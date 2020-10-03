/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Header file of the board module */

#ifndef BOARD_H
#define BOARD_H

#include "queue.h"
#include <stdbool.h>
/* Note: feel free to modify this API if you need it to clean your code */

/* We want a 30x30 board game by default */
#define BOARD_SIZE 30
#define NB_CASES (BOARD_SIZE * BOARD_SIZE)
#define NB_COLORS 7

#define PLAYER1 '1'
#define PLAYER2 '2'

extern char board[BOARD_SIZE * BOARD_SIZE]; // Filled with zeros
extern point start1, start2;

extern const char colors[];
extern const point direction[];

/** Retrieves the color of a given board cell */
char get_cell(int x, int y);

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color);

void init_board();

void propagate(point *p, char curr_player, char color, bool *change, int *score1, int *score2);
void bad_update_board(char curr_player, char color, int *score1, int *score2);

void visit_bfs(point *p, bool *seen, queue *q, char player, char color, int *score1, int *score2);
void update_board_bfs(char player, char color, int *score1, int *score2);

#endif
