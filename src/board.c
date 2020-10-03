#include "board.h"
#include "simple_unit_test.h" /* Import the testing infrastructure */

/* Note: This template comes with several global definitions. For now.
 *
 * Such globals are usually discouraged, but having a few of them is OK in a C program.
 * At first, no dinosaure will get you if you use globals, but you should seek for a better
 * solution for your final version.
 *
 * Encapuslating them in an appropriate data structure, and removing all globals would be a must.
 * Plus, this path often leads to simpler code, that is easier to test.
 */

const char colors[] = {'R', 'V', 'B', 'J', 'G', 'M', 'C'};
char board[BOARD_SIZE * BOARD_SIZE] = {0}; // Filled with zeros
point start1 = {BOARD_SIZE - 1, 0}, start2 = {0, BOARD_SIZE - 1};
const point direction[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// init the board with random colors
void init_board()
{
    char color;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            color = random_color();
            set_cell(i, j, color);
        }
    }
    set_cell(start1.x, start1.y, PLAYER1);
    set_cell(start2.x, start2.y, PLAYER2);
}

void propagate(point *p, char curr_player, char color, bool *change, int *score1, int *score2)
{
    point pvoisin;
    for (int k = 0; k < 4; k++)
    {
        pvoisin.x = p->x + direction[k].x;
        pvoisin.y = p->y + direction[k].y;
        bool in_bounds = (pvoisin.x >= 0 && pvoisin.x < BOARD_SIZE && pvoisin.y >= 0 && pvoisin.y < BOARD_SIZE);
        bool chosen_color = (get_cell(pvoisin.x, pvoisin.y) == color);
        if (in_bounds && chosen_color)
        {
            *change = true;
            set_cell(pvoisin.x, pvoisin.y, curr_player);
            if (curr_player == PLAYER1)
                (*score1)++;
            else
                (*score2)++;
            propagate(&pvoisin, curr_player, color, change, score1, score2);
        }
    }
}

void bad_update_board(char curr_player, char color, int *score1, int *score2)
{
    bool change = true;
    point *p = (point *)malloc(sizeof(point));
    while (change)
    {
        change = false;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (get_cell(i, j) == curr_player)
                {
                    p->x = i;
                    p->y = j;
                    propagate(p, curr_player, color, &change, score1, score2);
                }
            }
        }
    }
    free(p);
}

void visit_bfs(point *p, bool *seen, queue *visit, char player, char color, int *score1, int *score2)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        if (get_cell(p->x, p->y) == color)
        {
            set_cell(p->x, p->y, player);
            if (player == PLAYER1)
                (*score1)++;
            else
                (*score2)++;
        }
        if (get_cell(p->x, p->y) == player)
        {
            int x, y;
            for (int k = 0; k < 4; k++)
            {
                x = p->x + direction[k].x;
                y = p->y + direction[k].y;
                bool in_bounds = (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
                if (in_bounds)
                {
                    point voisin = {x, y};
                    add_queue(visit, &voisin);
                }
            }
        }
    }
}

void update_board_bfs(char player, char color, int *score1, int *score2)
{
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    if (player == PLAYER1)
        add_queue(visit, &start1);
    else
        add_queue(visit, &start2);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        visit_bfs(p, seen, visit, player, color, score1, score2);
    }
    free(p);
    free(visit);
}

/************ The tests **************/

/* Tests that the initialization works */
SUT_TEST(init_cell)
{
    char c = get_cell(5, 5);
    SUT_CHAR_EQUAL(c, '\0', "Creating the board does not initialize the cells to '\\0' but to '%c'", c);

    return 1;
}

/* Tests that the get_cell and set_cell work */
SUT_TEST(getset_cell)
{
    char c;

    set_cell(5, 5, 'A');
    c = get_cell(5, 5);
    SUT_CHAR_EQUAL(c, 'A', "Setting a cell to 'A' leads to '%c' as a value instead", c);

    return 1;
}

SUT_TEST_SUITE(board) = {
    SUT_TEST_SUITE_ADD(init_cell),
    SUT_TEST_SUITE_ADD(getset_cell),
    SUT_TEST_SUITE_END};
