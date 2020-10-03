#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void clear_buffer();

int choose_game_mode();

int run_two_players_game(int *score1, int* score2);
int run_single_player_game(int *score1, int* score2);

bool in_colors(char c);
char get_player_move();
void change_player(char *curr_player, int *tour);

bool new_game();

#endif
