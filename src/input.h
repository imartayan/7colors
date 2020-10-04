#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdbool.h>
#include "defaults.h"
#include "display.h"

void clear_buffer();
int ask_int(int lower_bound, int upper_bound);
void choose_game_mode(int *mode);
bool in_colors(char c);
char ask_player_move();
char get_player_move(char player);
bool ask_new_game();

#endif
