#ifndef DISPLAY_H
#define DISPLAY_H

#include "structures.h"

void reset_print_color();
void set_print_color(char c);
void print_welcome_screen();
void print_score(State *state);
void print_turn(int turn, char player);
void print_board(char *board, int board_size);
void print_end_screen(char winner, State *state);
void print_statistics(State *state, int nb_games, int wins1, int wins2, int total1, int total2);

#endif
