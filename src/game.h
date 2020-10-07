#ifndef GAME_H
#define GAME_H

typedef char (*strategy)(pstate);

void next_player(char *player, int *turn);
void select_strategy(int *mode, strategy *strat);
void run_game(pstate state, strategy strat1, strategy strat2, bool wait);
void run_fast_game(pstate state, strategy strat1, strategy strat2);

#endif
