#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "defaults.h"
#include "utils.h"

void reset_print_color();
void set_print_color(char c);
void print_welcome_screen();
void print_score(int score1, int score2);
void print_turn(char player, int turn);
void print_board();
void print_end_screen(char winner, int mode, int score1, int score2);

#endif
