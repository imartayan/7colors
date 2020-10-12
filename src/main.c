#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "utils.h"
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
    int board_size = 30;
    int nb_cases = board_size * board_size;
    char *board = malloc(nb_cases * sizeof(char));
    point start1 = {0, 0}, start2 = {board_size - 1, board_size - 1};
    Player player1 = {PLAYER1, 1, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, board_size, &player1, &player2, &player1, '?', 1};
    int mode[3];
    choose_game_mode(mode);
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
            init_board(&state);
            state.curr_player = &player1;
            winner = run_game(&state, strat1, strat2, wait);
            print_end_screen(winner, &state);
            continue_playing = ask_new_game();
        }
    }
    else
    {
        int nb_games = 20;
        int wins1 = 0;
        int wins2 = 0;
        int total1 = 0;
        int total2 = 0;
        char *board_cpy = malloc(nb_cases * sizeof(char));
        for (int i = 0; i < nb_games; i++)
        {
            printf("%d ", i + 1);
            fflush(stdout);
            if (i % 2 == 0)
            {
                init_board(&state);
                memcpy(board_cpy, state.board, nb_cases);
                state.curr_player = &player1;
            }
            else
            {
                memcpy(state.board, board_cpy, nb_cases);
                state.curr_player = &player2;
            }
            winner = run_fast_game(&state, strat1, strat2);
            if (winner == player1.id)
                wins1++;
            else if (winner == player2.id)
                wins2++;
            total1 += player1.score;
            total2 += player2.score;
        }
        free(board_cpy);
        print_statistics(&state, nb_games, wins1, wins2, total1, total2);
    }
    free(board);
    return 0; // Everything went well
}
