#include <stdbool.h>
#include <time.h>
#include "display.h"
#include "input.h"
#include "board.h"
#include "game.h"

/** Program entry point */
int main(void)
{
    srand((unsigned)time(NULL));
    print_welcome_screen();
    int mode = choose_game_mode();
    int score1, score2;
    int winner;
    bool continue_playing = true;
    while (continue_playing)
    {
        init_board();
        score1 = score2 = 1;
        if (mode == 1)
            winner = run_single_player_game(&score1, &score2);
        else if (mode == 2)
            winner = run_two_players_game(&score1, &score2);
        print_end_screen(winner, mode, score1, score2);
        continue_playing = ask_new_game();
    }
    return 0; // Everything went well
}
