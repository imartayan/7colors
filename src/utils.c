#include <stdlib.h>
#include "utils.h"
#include "defaults.h"
#include "simple_unit_test.h"

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

bool game_ended(int score1, int score2, int score_max)
{
    return (score1 * 2 > score_max) || (score2 * 2 > score_max) || (score1 + score2 == score_max);
}

/************ Tests **************/

SUT_TEST(_get_cell)
{
    char board[] = {'1', 'R', 'G', 'C', 'J', 'M', 'V', 'B', '2'};
    char c = get_cell(board, 3, 0, 1);
    SUT_CHAR_EQUAL(c, 'C', "get_cell reads '%c' instead of 'C'.", c);
    return 1;
}

SUT_TEST(_set_cell)
{
    char board[] = {'1', 'R', 'G', 'C', 'J', 'M', 'V', 'B', '2'};
    set_cell(board, 3, 0, 1, 'V');
    char c = get_cell(board, 3, 0, 1);
    SUT_CHAR_EQUAL(c, 'V', "The cell contains '%c' instead of 'V'.", c);
    return 1;
}

SUT_TEST(_in_bounds)
{
    bool b = in_bounds(3, 1, 4);
    SUT_ASSERT_FALSE(b, "These coordinates should be out of bounds.");
    b = in_bounds(3, 2, 2);
    SUT_ASSERT_TRUE(b, "These coordinates should be in bounds.");
    return 1;
}

SUT_TEST(_count_true)
{
    bool tab[] = {true, false, false, true};
    int c = count_true(tab, 4);
    SUT_INT_EQUAL(c, 2, "The count of true values is wrong.");
    return 1;
}

SUT_TEST(_get_nth_true)
{
    bool tab[] = {true, false, false, true};
    int c = get_nth_true(tab, 4, 2);
    SUT_INT_EQUAL(c, 3, "The index returned by get_nth_true is incorrect");
    return 1;
}

SUT_TEST(_game_ended)
{
    bool b = game_ended(3, 4, 9);
    SUT_ASSERT_FALSE(b, "The game should not be ended.");
    b = game_ended(3, 5, 9);
    SUT_ASSERT_TRUE(b, "The game should be ended.");
    return 1;
}

SUT_TEST_SUITE(utils) = {
    SUT_TEST_SUITE_ADD(_get_cell),
    SUT_TEST_SUITE_ADD(_set_cell),
    SUT_TEST_SUITE_ADD(_in_bounds),
    SUT_TEST_SUITE_ADD(_count_true),
    SUT_TEST_SUITE_ADD(_get_nth_true),
    SUT_TEST_SUITE_ADD(_game_ended),
    SUT_TEST_SUITE_END};
