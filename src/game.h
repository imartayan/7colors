#ifndef GAME_H
#define GAME_H

void next_player(char *player, int *turn);
char run_game(int *score1, int *score2, char (*move1)(char), char (*move2)(char), bool wait);
char run_game_fast(int *score1, int *score2, char (*move1)(char), char (*move2)(char));

#endif
