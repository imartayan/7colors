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

// main game function, contains the game cycle, returns the winning player
char run_game(int *score1, int *score2, char (*move1)(char), char (*move2)(char), bool wait)
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
            color = (*move1)(player);
            update_board(player, color, score1);
        }
        else
        {
            color = (*move2)(player);
            update_board(player, color, score2);
        }
        if (wait)
        {
            clock_t t0 = clock();
            clock_t t1 = clock();
            while (t1 - t0 < CLOCKS_PER_SEC / 4)
            {
                t1 = clock();
            }
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
