#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

void clear_buffer();
int ask_int(int lower_bound, int upper_bound);
void choose_game_mode(int *mode);
bool in_colors(char c);
char ask_player_move();
bool ask_new_game();

#endif
