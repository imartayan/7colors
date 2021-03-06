/*******************************************************
Role ........ :
Auteurs ...... : Clément MORAND, Igor Martayan
dernière modification : 12/10/2020
Licence ..... : GNU General Public License v3.0
compilation : utilisez le CMakeList
execution : pour lancer le mode de tournoi taper ./7colors n
  où n est le nombre de parties à faire jouer dans le tournoi
********************************************************/
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
#include "server.h"

/** Program entry point */
int main(int argc, char **argv)
{
    int server_socket = open_server();
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
        int client_socket = accept_spec(server_socket);
        //envoi du plateau
        send_message(client_socket, board, nb_cases);
        //envoi de la taille du plateau
        char* string_board_size = conversion_int_to_array(board_size);
        send_message(client_socket, string_board_size, strlen(string_board_size));
        free(string_board_size);
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
        // déconnecter le spectateur
        close_socket(client_socket);
    }
    else
    {
        int nb_games = 100;
        if (argc >= 2)
        {
            nb_games = atoi(argv[1]);
        }
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
            swap_player_position(&player1, &player2);
        }
        free(board_cpy);
        print_statistics(&state, nb_games, wins1, wins2, total1, total2);
    }
    free(board);
    close_socket(server_socket);
    return 0; // Everything went well
}
