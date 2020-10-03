/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h> /* Import the system's printf */
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "queue.h"
#include "board.h" /* Import our board module */
#include "display.h"
#include "game.h"

/** Program entry point */
int main(void)
{
    srand((unsigned)time(NULL));
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
           "*****************************************************\n\n"
           "Current board state:\n");
    int winner;
    int score1, score2;
    bool continue_playing = true;
    while(continue_playing){
      score1 = score2 = 1;
      init_board();
      int nb_players = choose_game_mode();
      if(nb_players == 1)
        winner = run_single_player_game(&score1, &score2);
      else if(nb_players == 2)
        winner = run_two_players_game(&score1, &score2);
      print_end_screen(winner, nb_players);
      continue_playing = new_game();
    }
    printf("Au revoir");
    return 0; // Everything went well
}
