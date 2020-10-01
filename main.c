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
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
           "*****************************************************\n\n"
           "Current board state:\n");
    init_board();
    print_board();
    char c;
    printf("quelle couleur voulez vous jouer ?");
    scanf("%c", &c);
    bad_update_board('1', c);
    print_board();

    return 0; // Everything went well
}
