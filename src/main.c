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
    bool continue_playing = true;
    while (continue_playing)
    {
        mode = choose_game_mode();
        init_board();
        score1 = score2 = 1;
        switch (mode)
        {
        case 1:
            // Partie à deux joueurs
            winner = run_game(&score1, &score2, get_player_move, get_player_move);
            break;
        case 2:
            // Partie contre une IA aveugle
            winner = run_game(&score1, &score2, get_player_move, random_color);
            break;
        case 3:
            // Partie contre une IA aléatoire
            winner = run_game(&score1, &score2, get_player_move, random_reachable_color);
            break;
        case 4:
            // Partie contre une IA gloutonne
            winner = run_game(&score1, &score2, get_player_move, best_reachable_color);
            break;
        case 5:
            // Partie contre une IA hégémonique
            winner = run_game(&score1, &score2, get_player_move, best_reachable_color);
            break;
        }
        print_end_screen(winner, mode, score1, score2);
        continue_playing = ask_new_game();
        system("clear");
    }
    return 0; // Everything went well
}
