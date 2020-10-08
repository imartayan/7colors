#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "defaults.h"
#include "display.h"
#include "input.h"
#include "game.h"
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
        *strat = best_perimeter_with_border;
        break;
    }
}

// main game function, contains the game cycle, returns the winning player
char run_game(State *state, strategy strat1, strategy strat2, bool wait)
{
    init_board(state);
    state->player1->score = 1;
    state->player2->score = 1;
    state->turn = 1;
    int score_max = state->board_size * state->board_size;
    char color;
    // game cycle
    while (state->player1->score + state->player2->score < score_max && 2 * state->player1->score <= score_max && 2 * state->player2->score <= score_max)
    {
        system("clear");
        print_score(state);
        print_board(state);
        print_turn(state);
        if (state->curr_player == state->player1)
        {
            color = (*strat1)(state);
            update_board(state, color);
            state->curr_player = state->player2;
        }
        else
        {
            color = (*strat2)(state);
            update_board(state, color);
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
    init_board(state);
    state->player1->score = 1;
    state->player2->score = 1;
    state->turn = 1;
    int score_max = state->board_size * state->board_size;
    char color;
    // game cycle
    while (state->player1->score + state->player2->score < score_max && 2 * state->player1->score <= score_max && 2 * state->player2->score <= score_max)
    {
        if (state->curr_player == state->player1)
        {
            color = (*strat1)(state);
            update_board(state, color);
            state->curr_player = state->player2;
        }
        else
        {
            color = (*strat2)(state);
            update_board(state, color);
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
