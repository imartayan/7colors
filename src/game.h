#ifndef GAME_H
#define GAME_H

void next_player(char *player, int *turn);
char run_game(int *score1, int *score2, char (*move1)(void), char (*move2)(void));

#endif
