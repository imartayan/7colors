#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include <string.h>
#include "defaults.h"
#include "structures.h"
#include "utils.h"
#include "board.h"

void init_state(pstate* new_state, pstate state);
void free_state(pstate state);
bool partie_finie(int score1, int score2);
int minimax(pstate state, bool maximizing_Player, char player);
char AI_minimax(pstate state);

void reachable_colors_bfs(char* board,point *p, bool *seen, queue *visit, char player, bool *reachable);
void reachable_colors(char* board,char player, bool *reachable);
char random_reachable_color(pstate state);

void color_score_bfs(char* board, point *p, bool *seen, queue *visit, char player, char color, int *score);
int color_score(char* board, char player, char color);
char best_score(pstate state);

int cell_expansion(char* board, point *p, char player);
void color_perimeter_bfs(char* board,point *p, bool *seen, queue *visit, char player, char color, int *perimeter);
int color_perimeter(char* board, char player, char color);
char best_perimeter(pstate state);

void color_perimeter_with_border_bfs(char* board, point *p, bool *seen, queue *visit, char player, char color, int *perimeter);
int color_perimeter_with_border(char* board, char player, char color);
char best_perimeter_with_border(pstate state);

#endif
