/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h> /* Import the system's printf */
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "queue.h"
#include "board.h" /* Import our board module */

/** Program entry point */
int main(void)
{
    srand((unsigned)time(NULL));
    init_board();
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
           "*****************************************************\n\n"
           "Current board state:\n");
    int winner = run_game();
    print_end_screen(winner);

    return 0; // Everything went well
}
