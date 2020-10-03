#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "display.h"
#include "input.h"
#include "game.h"
#include "AI.h"

/*main game function, contains the game cycle
 return the number of the winning player*/
char run_two_players_game(int *score1, int *score2)
{
    char color;
    int turn = 0;
    char curr_player = PLAYER2;
    // game cycle
    while (*score1 + *score2 < NB_CASES && 2 * *score1 <= NB_CASES && 2 * *score2 <= NB_CASES)
    {
        change_player(&curr_player, &turn);
        system("clear"); // efface la console
        print_score(*score1, *score2);
        print_board();
        print_turn(curr_player, turn);
        color = get_player_move();
        update_board_bfs(curr_player, color, score1, score2);
    }
    if (*score1 > *score2)
        return PLAYER1;
    else if (*score1 < *score2)
        return PLAYER2;
    else
        return '0';
}

char run_single_player_game(int *score1, int *score2)
{
    char color;
    int turn = 1;
    // game cycle
    while (*score1 + *score2 < NB_CASES && 2 * *score1 <= NB_CASES && 2 * *score2 <= NB_CASES)
    {
        system("clear"); // efface la console
        print_score(*score1, *score2);
        print_board();
        print_turn(PLAYER1, turn);
        color = get_player_move();
        update_board_bfs(PLAYER1, color, score1, score2);
        if (2 * *score1 <= NB_CASES)
        {
            // AI's turn
            color = get_AI_move();
            update_board_bfs(PLAYER2, color, score1, score2);
            if (2 * *score2 > NB_CASES)
                return PLAYER2;
        }
        else if (2 * *score1 == NB_CASES && 2 * *score2 == NB_CASES)
            return '0';
        turn++;
    }
    // the player wins
    return PLAYER1;
}

void change_player(char *curr_player, int *turn)
{
    if (*curr_player == PLAYER1)
        *curr_player = PLAYER2;
    else
    {
        *curr_player = PLAYER1;
        (*turn)++;
    }
}
