#include "board.h"
#include "defaults.h"
#include "utils.h"
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

// init the board with random colors
void init_board(Player *player1, Player *player2)
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
    set_cell(player1->start->x, player1->start->y, player1->id);
    set_cell(player2->start->x, player2->start->y, player2->id);
}

void propagate(point *p, Player *player, char color, bool *change)
{
    point voisin;
    for (int k = 0; k < 4; k++)
    {
        voisin.x = p->x + direction[k].x;
        voisin.y = p->y + direction[k].y;
        bool chosen_color = (get_cell(voisin.x, voisin.y) == color);
        if (in_bounds(voisin.x, voisin.y) && chosen_color)
        {
            *change = true;
            set_cell(voisin.x, voisin.y, player->id);
            (player->score)++;
            propagate(&voisin, player, color, change);
        }
    }
}

void bad_update_board(Player *player, char color)
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
                if (get_cell(i, j) == player->id)
                {
                    p->x = i;
                    p->y = j;
                    propagate(p, player, color, &change);
                }
            }
        }
    }
    free(p);
}

void update_board_bfs(point *p, bool *seen, queue *visit, Player *player, char color)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(p->x, p->y);
        if (cell_color == color)
        {
            set_cell(p->x, p->y, player->id);
            cell_color = player->id;
            (player->score)++;
        }
        if (cell_color == player->id)
        {
            int x, y;
            for (int k = 0; k < 4; k++)
            {
                x = p->x + direction[k].x;
                y = p->y + direction[k].y;
                if (in_bounds(x, y))
                {
                    point voisin = {x, y};
                    add_queue(visit, &voisin);
                }
            }
        }
    }
}

void update_board(Player *player, char color)
{
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    add_queue(visit, player->start);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        update_board_bfs(p, seen, visit, player, color);
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
