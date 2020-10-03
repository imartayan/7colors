#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include "defaults.h"
#include "structures.h"
#include "utils.h"
#include "board.h"

void reachable_color_bfs(point *p, bool *seen, queue *visit, char player, bool *reachable);
void reachable_colors(char player, bool *reachable);
char random_reachable_color();

void simulate_color_bfs(point *p, bool *seen, queue *visit, char player, char color, int *score);
int simulate_color(char player, char color);
char best_reachable_color();

#endif
