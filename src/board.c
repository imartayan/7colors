#include "board.h"
#include "utils.h"
#include "simple_unit_test.h"

const point direction[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// init the board with random colors
void init_board(State *state)
{
    char color;
    for (int i = 0; i < state->board_size; i++)
    {
        for (int j = 0; j < state->board_size; j++)
        {
            color = random_color();
            set_cell(state->board, state->board_size, i, j, color);
        }
    }
    set_cell(state->board, state->board_size, state->player1->start->x, state->player1->start->y, state->player1->id);
    set_cell(state->board, state->board_size, state->player2->start->x, state->player2->start->y, state->player2->id);
}

void propagate(point *p, State *state, char color, bool *change)
{
    point voisin;
    for (int k = 0; k < 4; k++)
    {
        voisin.x = p->x + direction[k].x;
        voisin.y = p->y + direction[k].y;
        bool chosen_color = (get_cell(state->board, state->board_size, voisin.x, voisin.y) == color);
        if (in_bounds(state->board_size, voisin.x, voisin.y) && chosen_color)
        {
            *change = true;
            set_cell(state->board, state->board_size, voisin.x, voisin.y, state->curr_player->id);
            (state->curr_player->score)++;
            propagate(&voisin, state, color, change);
        }
    }
}

void bad_update_board(State *state, char color)
{
    bool change = true;
    point *p = (point *)malloc(sizeof(point));
    while (change)
    {
        change = false;
        for (int i = 0; i < state->board_size; i++)
        {
            for (int j = 0; j < state->board_size; j++)
            {
                if (get_cell(state->board, state->board_size, i, j) == state->curr_player->id)
                {
                    p->x = i;
                    p->y = j;
                    propagate(p, state, color, &change);
                }
            }
        }
    }
    free(p);
}

void update_board_bfs(point *p, bool *seen, queue *visit, State *state, char color)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
        {
            set_cell(state->board, state->board_size, p->x, p->y, state->curr_player->id);
            cell_color = state->curr_player->id;
            (state->curr_player->score)++;
        }
        if (cell_color == state->curr_player->id)
        {
            int x, y;
            for (int k = 0; k < 4; k++)
            {
                x = p->x + direction[k].x;
                y = p->y + direction[k].y;
                if (in_bounds(state->board_size, x, y))
                {
                    point voisin = {x, y};
                    add_queue(visit, &voisin);
                }
            }
        }
    }
}

void update_board(State *state, char color)
{
    int nb_cells = state->board_size * state->board_size;
    bool *seen = (bool *)malloc(nb_cells * sizeof(bool));
    for (int i = 0; i < nb_cells; i++)
        seen[i] = false;
    queue *visit = create_queue();
    add_queue(visit, state->curr_player->start);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        update_board_bfs(p, seen, visit, state, color);
    }
    free(p);
    free(visit);
    free(seen);
}

/************ Tests **************/

SUT_TEST(test_update_board)
{
    char board[] = {'1', 'R', 'V', 'V', 'R', 'R', 'R', 'V', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 1, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 3, &player1, &player2, &player1, '?', 1};
    update_board(&state, 'R');
    char expected[] = {'1', '1', 'V', 'V', '1', '1', 'R', 'V', '2'};
    for (int x = 0; x < 2; x++)
        for (int y = 0; y < 2; y++)
            SUT_CHAR_EQUAL(board[x + 3 * y], expected[x + 3 * y], "The cell (%d,%d) is not correctly changed with update_board.", x, y);
    return 1;
}

SUT_TEST_SUITE(board) = {
    SUT_TEST_SUITE_ADD(test_update_board),
    SUT_TEST_SUITE_END};
