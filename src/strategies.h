#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include "structures.h"

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

void color_perimeter_with_border_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *perimeter);
int color_perimeter_with_border(State *state, char color);
char best_perimeter_with_border(State *state);

#endif
