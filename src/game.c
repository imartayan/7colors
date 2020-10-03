#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

/*main game function, contains the game cycle, returns the winning player*/
char run_game(char* board, int *score1, int *score2, char (*move1)(char*), char (*move2)(char*))
{
    char color;
    int turn = 1;
    char player = PLAYER1;
    // game cycle
    while (*score1 + *score2 < SCORE_MAX && 2 * *score1 <= SCORE_MAX && 2 * *score2 <= SCORE_MAX)
    {
        //system("clear");
        print_score(*score1, *score2);
        print_board(board);
        print_turn(player, turn);
        if (player == PLAYER1)
            color = (*move1)(board);
        else
            color = (*move2)(board);
        update_board_bfs(board, player, color, score1, score2);
        next_player(&player, &turn);
    }
    if (*score1 > *score2)
        return PLAYER1;
    else if (*score1 < *score2)
        return PLAYER2;
    else
        return '0';
}
