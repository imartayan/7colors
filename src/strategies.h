#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include "structures.h"

char play_human_move(Player *player);
char play_random_move(Player *player);

void reachable_colors_bfs(point *p, bool *seen, queue *visit, Player *player, bool *reachable);
void reachable_colors(Player *player, bool *reachable);
char random_reachable_color(Player *player);

void color_score_bfs(point *p, bool *seen, queue *visit, Player *player, char color, int *score);
int color_score(Player *player, char color);
char best_score(Player *player);

int cell_expansion(point *p, Player *player);

void color_perimeter_bfs(point *p, bool *seen, queue *visit, Player *player, char color, int *perimeter);
int color_perimeter(Player *player, char color);
char best_perimeter(Player *player);

void color_perimeter_with_border_bfs(point *p, bool *seen, queue *visit, Player *player, char color, int *perimeter);
int color_perimeter_with_border(Player *player, char color);
char best_perimeter_with_border(Player *player);

#endif
