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
// char run_game(int player1->score, int player2->score, strategy strat1, strategy strat2, bool wait)
char run_game(Player *player1, Player *player2, strategy strat1, strategy strat2, bool wait)
{
    char color;
    int turn = 1;
    Player *player = player1;
    // game cycle
    while (player1->score + player2->score < SCORE_MAX && 2 * player1->score <= SCORE_MAX && 2 * player2->score <= SCORE_MAX)
    {
        system("clear");
        print_score(player1->score, player2->score);
        print_board();
        print_turn(player->id, turn);
        if (player == player1)
        {
            color = (*strat1)(player);
            update_board(player, color);
            player = player2;
        }
        else
        {
            color = (*strat2)(player);
            update_board(player, color);
            player = player1;
            turn++;
        }
        if (wait)
            system("sleep 0.25s");
    }
    if (player1->score > player2->score)
        return player1->id;
    else if (player1->score < player2->score)
        return player2->id;
    else
        return '0';
}

char run_fast_game(Player *player1, Player *player2, strategy strat1, strategy strat2)
{
    char color;
    Player *player = player1;
    // game cycle
    while (player1->score + player2->score < SCORE_MAX && 2 * player1->score <= SCORE_MAX && 2 * player2->score <= SCORE_MAX)
    {
        if (player == player1)
        {
            color = (*strat1)(player);
            update_board(player, color);
            player = player2;
        }
        else
        {
            color = (*strat2)(player);
            update_board(player, color);
            player = player1;
        }
    }
    if (player1->score > player2->score)
        return player1->id;
    else if (player1->score < player2->score)
        return player2->id;
    else
        return '0';
}
