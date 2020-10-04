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
            winner = run_game(&score1, &score2, get_player_move, get_player_move, false);
            break;
        case 2:
            // Partie contre une IA aveugle
            winner = run_game(&score1, &score2, get_player_move, play_random_color, false);
            break;
        case 3:
            // Partie contre une IA aléatoire
            winner = run_game(&score1, &score2, get_player_move, random_reachable_color, false);
            break;
        case 4:
            // Partie contre une IA gloutonne
            winner = run_game(&score1, &score2, get_player_move, best_score, false);
            break;
        case 5:
            // Partie contre une IA hégémonique sans bord
            winner = run_game(&score1, &score2, get_player_move, best_perimeter, false);
            break;
        case 6:
            // Partie entre IA aléatoire et gloutonne
            winner = run_game(&score1, &score2, random_reachable_color, best_score, true);
            break;
        case 7:
            // Partie entre IA gloutonne et hégémonique sans bord
            winner = run_game(&score1, &score2, best_score, best_perimeter, true);
            break;
        case 8:
            // Partie entre IA gloutonne et hégémonique avec bord
            winner = run_game(&score1, &score2, best_score, best_perimeter_with_border, true);
            break;
        case 9:
            // Partie entre IA sans bord vs avec bord
            winner = run_game(&score1, &score2, best_perimeter, best_perimeter_with_border, true);
            break;
        }
        print_end_screen(winner, mode, score1, score2);
        continue_playing = ask_new_game();
        system("clear");
    }
    return 0; // Everything went well
}
