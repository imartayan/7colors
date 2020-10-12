#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include "structures.h"

#define MAX_DEPTH 3
#define MAX_DEPTH_PRUNING 5

char play_human_move(State *state);
char play_random_move(State *state);

void reachable_colors_visit(point *p, bool *seen, queue *to_visit, State *state, bool *reachable);
void reachable_colors(State *state, bool *reachable);
char random_reachable_color(State *state);

void compute_bfs(State *state, char color, int *val, visit_bfs visit);

void score_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *score);
int color_score(State *state, char color);
char best_score(State *state);

int cell_expansion(point *p, State *state);

void perimeter_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *perimeter);
int color_perimeter(State *state, char color);
char best_perimeter(State *state);

void perimeter_borderless_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *perimeter);
int color_perimeter_borderless(State *state, char color);
char best_perimeter_borderless(State *state);

void expansion_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *expansion);
int color_expansion(State *state, char color);
char best_expansion(State *state);

void expansion_borderless_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *expansion);
int color_expansion_borderless(State *state, char color);
char best_expansion_borderless(State *state);

point minimax(State *state, heuristic heur, int depth, int *alpha, int *beta, bool maximizing);
char harpagon(State *state);
char toyota(State *state);

#endif
