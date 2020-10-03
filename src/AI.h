#ifndef AI_H
#define AI_H

#include <stdbool.h>
#include "defaults.h"
#include "structures.h"
#include "utils.h"
#include "board.h"

char get_AI_move();

void visit_colors_bfs(point *p, bool *seen, queue *visit, char *possible_colors, int *nb_possible_colors);
void get_possible_colors_bfs(char *possible_colors, int *nb_possible_colors);

void print_possible_colors(char *possible_colors, int nb_possible_colors);
char random_possible_color();

#endif
