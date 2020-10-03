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
    int mode, score1, score2;
    char winner;
    char board[NB_CASES] = {0};
    bool continue_playing = true;
    while (continue_playing)
    {
        mode = choose_game_mode();
        init_board(board);
        score1 = score2 = 1;
        switch (mode)
        {
        case 1:
            // Partie à deux joueurs
            winner = run_game(board, &score1, &score2, get_player_move, get_player_move);
            break;
        case 2:
            // Partie contre une IA aléatoire
            winner = run_game(board, &score1, &score2, get_player_move, random_color);
            break;
        case 3:
            // Partie contre une IA qui tire aléatoirement parmis les couleurs qui font grandir sa zone
            winner = run_game(board, &score1, &score2, get_player_move, get_AI_move);
            break;
        case 4:
            // Partie contre une IA gloutonne
            winner = run_game(board, &score1, &score2, get_player_move, get_AI_move);
            break;
        case 5:
          //partie contre une IA hégémonique (qui cherche a maximiser le périmètre de sa zone)
          winner = run_game(board, &score1, &score2, get_player_move, get_AI_move);
          break;
        }


        print_end_screen(board, winner, mode, score1, score2);
        continue_playing = ask_new_game();
        system("clear");
    }
    return 0; // Everything went well
}
