#ifndef AI_H
#define AI_H

char random_color();
char get_AI_move();

void visit_colors_bfs(char* board, point *p, bool *seen, queue *visit, char *possible_colors, int *nb_possible_colors);
void get_possible_colors_bfs(char* board, char *possible_colors, int *nb_possible_colors);

void print_possible_colors(char *possible_colors, int nb_possible_colors);
char random_possible_color(char* board);

void hegemonic_update_board_bfs(char* board, char color, int *score);
void hegemonic_visit_bfs(char* board, point *p, bool *seen, queue *visit, char color, int *score);
char hegemonic_AI(char* board);

#endif
