#include <stdbool.h>
#include <time.h>
#include "display.h"
#include "input.h"
#include "board.h"
#include "game.h"
#include "AI.h"

/** Program entry point */
int main(void)
{
    srand((unsigned)time(NULL));
    print_welcome_screen();
    int mode[3];
    choose_game_mode(mode);
    strategy strat[2];
    select_strategy(mode, strat);
    int score1, score2;
    char winner;
    if (mode[0] == 1)
    {
        bool wait = !(mode[1] == 1 || mode[2] == 1);
        bool continue_playing = true;
        while (continue_playing)
        {
            init_board();
            score1 = score2 = 1;
            winner = run_game(&score1, &score2, strat[0], strat[1], wait);
            print_end_screen(winner, score1, score2);
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
            init_board();
            score1 = score2 = 1;
            winner = run_fast_game(&score1, &score2, strat[0], strat[1]);
            if (winner == PLAYER1)
                wins1++;
            else if (winner == PLAYER2)
                wins2++;
            total1 += score1;
            total2 += score2;
        }
        print_statistics(nb_games, wins1, wins2, total1, total2);
    }
    return 0; // Everything went well
}
