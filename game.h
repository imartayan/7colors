#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

bool in_colors(char c);
int run_game(int* score1,int* score2);
char get_player_move();
void change_player(char *curr_player, int *tour);

#endif
