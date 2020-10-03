#ifndef GAME_H
#define GAME_H

char run_two_players_game(int *score1, int *score2);
char run_single_player_game(int *score1, int *score2);
void change_player(char *curr_player, int *tour);

#endif
