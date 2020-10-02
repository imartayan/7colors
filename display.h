#ifndef DISPLAY_H
#define DISPLAY_H

void reset_print_color();
void set_print_color(char c);
void print_board(char curr_player, int tour, int score1, int score2);
void print_end_screen(int winner);

#endif
