#ifndef GAME_H
#define GAME_H

#include "structures.h"

void select_strategy(int player_type, strategy *strat);
void swap_player_position(Player *player1, Player *player2);
char run_game(State *state, strategy strat1, strategy strat2, bool wait);
char run_fast_game(State *state, strategy strat1, strategy strat2);

#endif
