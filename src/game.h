#ifndef GAME_H
#define GAME_H

typedef char (*strategy)(char);

void next_player(char *player, int *turn);
void select_strategy(int *mode, strategy *strat);
char run_game(int *score1, int *score2, strategy strat1, strategy strat2, bool wait);
char run_fast_game(int *score1, int *score2, strategy strat1, strategy strat2);

#endif
