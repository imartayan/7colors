#ifndef GAME_H
#define GAME_H

#include "structures.h"

void select_strategy(int player_type, strategy *strat);
char run_game(Player *player1, Player *player2, strategy strat1, strategy strat2, bool wait);
char run_fast_game(Player *player1, Player *player2, strategy strat1, strategy strat2);

#endif
