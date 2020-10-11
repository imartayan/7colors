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

void naive_update_board(State *state, char color)
{
    bool change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < state->board_size; i++)
        {
            for (int j = 0; j < state->board_size; j++)
            {
                if (get_cell(state->board, state->board_size, i, j) == state->curr_player->id)
                {
                    point voisin;
                    for (int k = 0; k < 4; k++)
                    {
                        voisin.x = i + direction[k].x;
                        voisin.y = j + direction[k].y;
                        if (in_bounds(state->board_size, voisin.x, voisin.y) && get_cell(state->board, state->board_size, voisin.x, voisin.y) == color)
                        {
                            change = true;
                            set_cell(state->board, state->board_size, voisin.x, voisin.y, state->curr_player->id);
                            (state->curr_player->score)++;
                        }
                    }
                }
            }
        }
    }
}

void propagate_color(point *p, State *state, char color, bool *change)
{
    point voisin;
    for (int k = 0; k < 4; k++)
    {
        voisin.x = p->x + direction[k].x;
        voisin.y = p->y + direction[k].y;
        if (in_bounds(state->board_size, voisin.x, voisin.y) && get_cell(state->board, state->board_size, voisin.x, voisin.y) == color)
        {
            *change = true;
            set_cell(state->board, state->board_size, voisin.x, voisin.y, state->curr_player->id);
            (state->curr_player->score)++;
            propagate_color(&voisin, state, color, change);
        }
    }
}

void recursive_update_board(State *state, char color)
{
    bool change = true;
    point p;
    for (int i = 0; i < state->board_size; i++)
    {
        for (int j = 0; j < state->board_size; j++)
        {
            if (get_cell(state->board, state->board_size, i, j) == state->curr_player->id)
            {
                p.x = i;
                p.y = j;
                propagate_color(&p, state, color, &change);
            }
        }
    }
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
    point p;
    while (!empty_queue(visit))
    {
        pop_queue(visit, &p);
        update_board_bfs(&p, seen, visit, state, color);
    }
    free(visit);
    free(seen);
}

/************ Tests **************/

SUT_TEST(test_naive_update_board)
{
    char board[] = {'1', 'R', 'V', 'V', 'R', 'R', 'R', 'V', '2'};
    char expected[] = {'1', '1', 'V', 'V', '1', '1', 'R', 'V', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 1, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 3, &player1, &player2, &player1, '?', 1};
    naive_update_board(&state, 'R');
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            SUT_CHAR_EQUAL(board[x + 3 * y], expected[x + 3 * y], "The cell (%d,%d) is not correctly changed with naive_update_board.", x, y);
    return 1;
}

SUT_TEST(test_recursive_update_board)
{
    char board[] = {'1', 'R', 'V', 'V', 'R', 'R', 'R', 'V', '2'};
    char expected[] = {'1', '1', 'V', 'V', '1', '1', 'R', 'V', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 1, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 3, &player1, &player2, &player1, '?', 1};
    recursive_update_board(&state, 'R');
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            SUT_CHAR_EQUAL(board[x + 3 * y], expected[x + 3 * y], "The cell (%d,%d) is not correctly changed with recursive_update_board.", x, y);
    return 1;
}

SUT_TEST(test_update_board)
{
    char board[] = {'1', 'R', 'V', 'V', 'R', 'R', 'R', 'V', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 1, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 3, &player1, &player2, &player1, '?', 1};
    update_board(&state, 'R');
    char expected[] = {'1', '1', 'V', 'V', '1', '1', 'R', 'V', '2'};
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            SUT_CHAR_EQUAL(board[x + 3 * y], expected[x + 3 * y], "The cell (%d,%d) is not correctly changed with update_board.", x, y);
    return 1;
}

SUT_TEST(test_consistent_update_board)
{
    point start1 = {0, 0}, start2 = {29, 29};
    Player player1 = {PLAYER1, 1, &start1}, player2 = {PLAYER2, 1, &start2};
    char board1[30 * 30];
    State state1 = {board1, 30, &player1, &player2, &player1, '?', 1};
    init_board(&state1);
    char board2[30 * 30];
    memcpy(board2, board1, 30 * 30);
    State state2 = {board2, 30, &player1, &player2, &player1, '?', 1};
    char board3[30 * 30];
    memcpy(board3, board1, 30 * 30);
    State state3 = {board3, 30, &player1, &player2, &player1, '?', 1};
    for (int i = 0; i < NB_COLORS; i++)
    {
        naive_update_board(&state1, colors[i]);
        recursive_update_board(&state2, colors[i]);
        update_board(&state3, colors[i]);
    }
    for (int x = 0; x < 30; x++)
        for (int y = 0; y < 30; y++)
        {
            SUT_CHAR_EQUAL(board1[x + 30 * y], board2[x + 30 * y], "The cell (%d,%d) is different after calling naive_update_board and recursive_update_board.", x, y);
            SUT_CHAR_EQUAL(board2[x + 30 * y], board3[x + 30 * y], "The cell (%d,%d) is different after calling recursive_update_board and update_board.", x, y);
        }
    return 1;
}

SUT_TEST_SUITE(board) = {
    SUT_TEST_SUITE_ADD(test_naive_update_board),
    SUT_TEST_SUITE_ADD(test_recursive_update_board),
    SUT_TEST_SUITE_ADD(test_update_board),
    SUT_TEST_SUITE_ADD(test_consistent_update_board),
    SUT_TEST_SUITE_END};
