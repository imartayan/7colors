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
    init_board();
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
           "*****************************************************\n\n"
           "Current board state:\n");
    int score1 = 1, score2 = 1;
    int winner = run_game(&score1, &score2);
    print_end_screen(winner);

    return 0; // Everything went well
}
