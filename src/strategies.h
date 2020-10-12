#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include "structures.h"

#define MAX_DEPTH 3
#define MAX_DEPTH_PRUNING 5

char play_human_move(State *state);
char play_random_move(State *state);

void reachable_colors_bfs(point *p, bool *seen, queue *visit, State *state, bool *reachable);
void reachable_colors(State *state, bool *reachable);
char random_reachable_color(State *state);

void color_score_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *score);
int color_score(State *state, char color);
char best_score(State *state);

int cell_expansion(point *p, State *state);

void color_perimeter_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *perimeter);
int color_perimeter(State *state, char color);
char best_perimeter(State *state);

void color_perimeter_borderless_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *perimeter);
int color_perimeter_borderless(State *state, char color);
char best_perimeter_borderless(State *state);

void color_expansion_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *expansion);
int color_expansion(State *state, char color);
char best_expansion(State *state);

void color_expansion_borderless_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *expansion);
int color_expansion_borderless(State *state, char color);
char best_expansion_borderless(State *state);

int minimax(State *state, int depth, bool maximizing_Player, char player_id);
char get_minimax(State *state);

int alpha_beta_pruning_minimax(State *state, int depth, bool maximizing_Player, char player_id, int *alpha, int *beta);
char get_minimax_pruning(State *state);

#endif
