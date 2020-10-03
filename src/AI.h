#ifndef AI_H
#define AI_H

char random_color();
char get_AI_move();

void visit_colors_bfs(point *p, bool *seen, queue *visit, char *possible_colors, int *nb_possible_colors);
void get_possible_colors_bfs(char *possible_colors, int *nb_possible_colors);

void print_possible_colors(char *possible_colors, int nb_possible_colors);
char random_possible_color();

#endif
