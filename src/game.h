#ifndef GAME_H
#define GAME_H

void next_player(char *player, int *turn);
char run_game(char* board, int *score1, int *score2, char (*move1)(char* board), char (*move2)(char* board));

#endif
