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

bool in_bounds(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
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

int color_id(char c)
{
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (c == colors[i])
            return i;
    }
    return -1;
}

int count_true(bool *tab, int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (tab[i])
            count++;
    }
    return count;
}

int get_nth_true(bool *tab, int len, int n)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (tab[i])
            count++;
        if (count == n)
            return i;
    }
    return -1;
}
