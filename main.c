/* Template of the 7 wonders of the world of the 7 colors assigment. */

#include <stdio.h>     /* Import the system's printf */
#include "board.h"     /* Import our board module */

/** Program entry point */
int main(void)
{
    printf("\n\nWelcome to the 7 wonders of the world of the 7 colors\n"
	   "*****************************************************\n\n"
	   "Current board state:\n");

    print_board();

    return 0; // Everything went well
}
