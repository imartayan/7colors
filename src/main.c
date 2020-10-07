#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "structures.h"
#include "defaults.h"
#include "display.h"
#include "input.h"
#include "board.h"
#include "game.h"
#include "strategies.h"

/** Program entry point */
int main(void)
{
    srand((unsigned)time(NULL));
    print_welcome_screen();
    int mode[3];
    choose_game_mode(mode);
    point start1 = {BOARD_SIZE - 1, 0}, start2 = {0, BOARD_SIZE - 1};
    Player player1 = {PLAYER1, 1, &start1}, player2 = {PLAYER2, 1, &start2};
    strategy strat1, strat2;
    select_strategy(mode[1], &strat1);
    select_strategy(mode[2], &strat2);
    char winner;
    if (mode[0] == 1)
    {
        bool wait = !(mode[1] == 1 || mode[2] == 1);
        bool continue_playing = true;
        while (continue_playing)
        {
            init_board(&player1, &player2);
            player1.score = 1;
            player2.score = 1;
            winner = run_game(&player1, &player2, strat1, strat2, wait);
            print_end_screen(winner, player1.score, player2.score);
            continue_playing = ask_new_game();
        }
    }
    else
    {
        int nb_games = 100;
        int wins1 = 0;
        int wins2 = 0;
        int total1 = 0;
        int total2 = 0;
        for (int i = 0; i < nb_games; i++)
        {
            init_board(&player1, &player2);
            player1.score = 1;
            player2.score = 1;
            if (i % 2 == 0)
                winner = run_fast_game(&player1, &player2, strat1, strat2);
            else
                winner = run_fast_game(&player2, &player1, strat2, strat1);
            if (winner == player1.id)
                wins1++;
            else if (winner == player2.id)
                wins2++;
            total1 += player1.score;
            total2 += player2.score;
        }
        print_statistics(nb_games, wins1, wins2, total1, total2);
    }
    return 0; // Everything went well
}
