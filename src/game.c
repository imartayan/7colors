#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "display.h"
#include "input.h"
#include "game.h"
#include "utils.h"
#include "strategies.h"

void select_strategy(int player_type, strategy *strat)
{
    switch (player_type)
    {
    case 1:
        *strat = play_human_move;
        break;
    case 2:
        *strat = play_random_move;
        break;
    case 3:
        *strat = random_reachable_color;
        break;
    case 4:
        *strat = best_score;
        break;
    case 5:
        *strat = best_perimeter;
        break;
    case 6:
        *strat = best_perimeter_borderless;
        break;
    case 7:
        *strat = best_expansion;
        break;
    case 8:
        *strat = best_expansion_borderless;
        break;
    case 9:
        *strat = get_minimax;
        break;
    case 10:
        *strat = get_harpagon;
        break;
    }
}

// main game function, contains the game cycle, returns the winning player
char run_game(State *state, strategy strat1, strategy strat2, bool wait)
{
    state->player1->score = 1;
    state->player2->score = 1;
    state->turn = 1;
    int score_max = state->board_size * state->board_size;
    // game cycle
    while (!game_ended(state->player1->score, state->player2->score, score_max))
    {
        system("clear");
        print_score(state);
        print_board(state->board, state->board_size);
        print_turn(state->turn, state->curr_player->id);
        if (state->curr_player == state->player1)
        {
            state->curr_move = (*strat1)(state);
            update_board(state);
            state->curr_player = state->player2;
        }
        else
        {
            state->curr_move = (*strat2)(state);
            update_board(state);
            state->curr_player = state->player1;
        }
        state->turn++;
        if (wait)
            system("sleep 0.25s");
    }
    if (state->player1->score > state->player2->score)
        return state->player1->id;
    else if (state->player1->score < state->player2->score)
        return state->player2->id;
    else
        return '0';
}

char run_fast_game(State *state, strategy strat1, strategy strat2)
{
    state->player1->score = 1;
    state->player2->score = 1;
    state->turn = 1;
    int score_max = state->board_size * state->board_size;
    // game cycle
    while (!game_ended(state->player1->score, state->player2->score, score_max))
    {
        if (state->curr_player == state->player1)
        {
            state->curr_move = (*strat1)(state);
            update_board(state);
            state->curr_player = state->player2;
        }
        else
        {
            state->curr_move = (*strat2)(state);
            update_board(state);
            state->curr_player = state->player1;
        }
        state->turn++;
    }
    if (state->player1->score > state->player2->score)
        return state->player1->id;
    else if (state->player1->score < state->player2->score)
        return state->player2->id;
    else
        return '0';
}
