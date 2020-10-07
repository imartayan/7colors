#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "display.h"
#include "input.h"
#include "game.h"
#include "AI.h"

void next_player(char *player, int *turn)
{
    if (*player == PLAYER1)
        *player = PLAYER2;
    else
    {
        *player = PLAYER1;
        (*turn)++;
    }
}

void select_strategy(int *mode, strategy *strat)
{
    for (int i = 0; i < 2; i++)
    {
        switch (mode[i + 1])
        {
        case 1:
            strat[i] = get_player_move;
            break;
        case 2:
            strat[i] = play_random_color;
            break;
        case 3:
            strat[i] = random_reachable_color;
            break;
        case 4:
            strat[i] = best_score;
            break;
        case 5:
            strat[i] = best_perimeter;
            break;
        case 6:
            strat[i] = best_perimeter_with_border;
            break;
        case 7:
            strat[i] = AI_minimax;
            break;
        }
    }
}

// main game function, contains the game cycle, state->curr_player is the winner when the function ends
void run_game(pstate state, strategy strat1, strategy strat2, bool wait)
{
    char color;
    int turn = 1;
    state->curr_player = PLAYER1;
    // game cycle
    while ((state->score1 + state->score2) < SCORE_MAX && (2 * state->score1 <= SCORE_MAX) && (2 * state->score2 <= SCORE_MAX))
    {
        system("clear");
        print_score(state->score1, state->score2);
        print_board(state->board);
        print_turn(state->curr_player, turn);
        if (state->curr_player == PLAYER1)
        {
            color = (*strat1)(state);
            state->last_move = color;
            update_board_bfs(state);
        }
        else
        {
            color = (*strat2)(state);
            state->last_move = color;
            update_board_bfs(state);
        }
        if (wait)
            system("sleep 0.25s");
        next_player(&(state->curr_player), &turn);
    }
    if (state->score1 > state->score2)
        state->curr_player = PLAYER1;
    else if (state->score1 < state->score2)
        state->curr_player = PLAYER2;
    else
        state->curr_player = '0';
}

void run_fast_game(pstate state, strategy strat1, strategy strat2)
{
    char color;
    int turn = 1;
    state -> curr_player = PLAYER1;
    // game cycle
    while ((state->score1 + state->score2) < SCORE_MAX && (2 * state->score1 <= SCORE_MAX) && (2 * state->score2 <= SCORE_MAX))
    {
        if (state -> curr_player == PLAYER1)
        {
            color = (*strat1)(state);
            state->last_move = color;
            update_board_bfs(state);
        }
        else
        {
            color = (*strat2)(state);
            state->last_move = color;
            update_board_bfs(state);
        }
        next_player(&(state->curr_player), &turn);
    }
    if (state->score1 > state->score2)
        state->curr_player = PLAYER1;
    else if (state->score1 < state->score2)
        state->curr_player = PLAYER2;
    else
        state->curr_player = '0';
}
