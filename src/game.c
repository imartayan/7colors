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
        }
    }
}

// main game function, contains the game cycle, returns the winning player
char run_game(int *score1, int *score2, strategy strat1, strategy strat2, bool wait)
{
    char color;
    int turn = 1;
    char player = PLAYER1;
    // game cycle
    while (*score1 + *score2 < SCORE_MAX && 2 * *score1 <= SCORE_MAX && 2 * *score2 <= SCORE_MAX)
    {
        system("clear");
        print_score(*score1, *score2);
        print_board();
        print_turn(player, turn);
        if (player == PLAYER1)
        {
            color = (*strat1)(player);
            update_board(player, color, score1);
        }
        else
        {
            color = (*strat2)(player);
            update_board(player, color, score2);
        }
        if (wait)
            system("sleep 0.25s");
        next_player(&player, &turn);
    }
    if (*score1 > *score2)
        return PLAYER1;
    else if (*score1 < *score2)
        return PLAYER2;
    else
        return '0';
}

char run_fast_game(int *score1, int *score2, strategy strat1, strategy strat2)
{
    char color;
    int turn = 1;
    char player = PLAYER1;
    // game cycle
    while (*score1 + *score2 < SCORE_MAX && 2 * *score1 <= SCORE_MAX && 2 * *score2 <= SCORE_MAX)
    {
        if (player == PLAYER1)
        {
            color = (*strat1)(player);
            update_board(player, color, score1);
        }
        else
        {
            color = (*strat2)(player);
            update_board(player, color, score2);
        }
        next_player(&player, &turn);
    }
    if (*score1 > *score2)
        return PLAYER1;
    else if (*score1 < *score2)
        return PLAYER2;
    else
        return '0';
}
