#include <stdlib.h>
#include "utils.h"
#include "defaults.h"

/** Retrieves the color of a given board cell */
char get_cell(char *board, int board_size, int x, int y)
{
    return board[x + y * board_size];
}

/** Changes the color of a given board cell */
void set_cell(char *board, int board_size, int x, int y, char color)
{
    board[x + y * board_size] = color;
}

bool in_bounds(int board_size, int x, int y)
{
    return x >= 0 && x < board_size && y >= 0 && y < board_size;
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

bool partie_finie(int score1, int score2, int max_score){
  return ((score1 * 2 > max_score || (score2 * 2 > max_score) || (score1 + score2 == max_score));
}
