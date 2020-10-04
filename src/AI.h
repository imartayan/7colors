#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include "defaults.h"
#include "structures.h"
#include "utils.h"
#include "board.h"

void reachable_colors_bfs(point *p, bool *seen, queue *visit, char player, bool *reachable);
void reachable_colors(char player, bool *reachable);
char random_reachable_color(char player);

void color_score_bfs(point *p, bool *seen, queue *visit, char player, char color, int *score);
int color_score(char player, char color);
char best_score_color(char player);

int expansion(point *p);

void color_perimeter_bfs(point *p, bool *seen, queue *visit, char player, char color, int *perimeter);
int color_perimeter(char player, char color);
char best_perimeter_color(char player);

void color_perimeter_with_border_bfs(point *p, bool *seen, queue *visit, char player, char color, int *perimeter);
int color_perimeter_with_border(char player, char color);
char best_perimeter_with_border_color(char player);

#endif
