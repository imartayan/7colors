/* Template of the 7 wonders of the world of the 7 colors assigment */
/* Header file of the board module */

#ifndef BOARD_H
#define BOARD_H

/* Note: feel free to modify this API if you need it to clean your code */

/* We want a 30x30 board game by default */
#define BOARD_SIZE 30

#define NB_COLORS 7


/** Retrieves the color of a given board cell */
char get_cell(int x, int y);

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color);

void init_board();
void update_board(char curr_player, char color);

/** Prints the current state of the board on screen
 *
 * It would be nicer to do this with ncurse or even SFML or SDL,
 * but this is not required in this assignment. See the extensions.
 */
void print_board(void);

#endif
