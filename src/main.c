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
    char board[NB_CASES] = {0};
    struct state state = {'\0', board, 1, 1, '\0'};
    if (mode[0] == 1)
    {
        bool wait = !(mode[1] == 1 || mode[2] == 1);
        bool continue_playing = true;
        while (continue_playing)
        {
            init_board(state.board);
            state.score1 = 1; state.score2 = 1;
            run_game(&state, strat[0], strat[1], wait);
            print_end_screen(&state);
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
            init_board(state.board);
            run_fast_game(&state, strat[0], strat[1]);
            if (state.curr_player == PLAYER1)
                wins1++;
            else if (state.curr_player == PLAYER2)
                wins2++;
            total1 += state.score1;
            total2 += state.score2;
        }
        print_statistics(nb_games, wins1, wins2, total1, total2);
    }
    return 0; // Everything went well
}
