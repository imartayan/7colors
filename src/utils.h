/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Header file of the board module */

#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define PLAYER1 '1'
#define PLAYER2 '2'
#define NB_COLORS 7

const char colors[NB_COLORS];

/** Retrieves the color of a given board cell */
char get_cell(char *board, int board_size, int x, int y);

/** Changes the color of a given board cell */
void set_cell(char *board, int board_size, int x, int y, char color);

bool in_bounds(int board_size, int x, int y);

int randint(int n);

char random_color();

int color_id(char c);

int count_true(bool *tab, int len);
int get_nth_true(bool *tab, int len, int n);

bool game_ended(int score1, int score2, int score_max);

#endif
