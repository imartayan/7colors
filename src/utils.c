#include "utils.h"

/** Retrieves the color of a given board cell */
char get_cell(int x, int y)
{
    return board[x + y * BOARD_SIZE];
}

/** Changes the color of a given board cell */
void set_cell(int x, int y, char color)
{
    board[x + y * BOARD_SIZE] = color;
}

int randint(int n)
{
    return rand() % n;
}

char random_color()
{
    int n = randint(NB_COLORS);
    return colors[n];
}
