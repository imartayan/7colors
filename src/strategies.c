/*******************************************************
Role ........ : Définition des différentes stratégies qui peuvent être utilisées par les joueurs durant la partie
Auteurs ...... : Clément MORAND, Igor Martayan
dernière modification : 12/10/2020
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "strategies.h"
#include "utils.h"
#include "display.h"
#include "input.h"
#include "board.h"
#include "simple_unit_test.h"

char play_human_move(State *state)
{
    return ask_player_move();
}

char play_random_move(State *state)
{
    return random_color();
}

void reachable_colors_visit(point *p, bool *seen, queue *to_visit, State *state, bool *reachable)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
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
                    add_queue(to_visit, &voisin);
                }
            }
        }
        else
        {
            int i = color_id(cell_color);
            if (i >= 0)
                reachable[i] = true;
        }
    }
}

void reachable_colors(State *state, bool *reachable)
{
    int nb_cells = state->board_size * state->board_size;
    bool *seen = (bool *)malloc(nb_cells * sizeof(bool));
    for (int i = 0; i < nb_cells; i++)
        seen[i] = false;
    queue *to_visit = create_queue();
    add_queue(to_visit, state->curr_player->start);
    point p;
    while (!empty_queue(to_visit))
    {
        pop_queue(to_visit, &p);
        reachable_colors_visit(&p, seen, to_visit, state, reachable);
    }
    free(to_visit);
    free(seen);
}

char random_reachable_color(State *state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state, reachable);
    int count = count_true(reachable, NB_COLORS);
    if (count)
    {
        int n = 1 + randint(count);
        return colors[get_nth_true(reachable, NB_COLORS, n)];
    }
    else
        return random_color();
}

void compute_bfs(State *state, char color, int *val, visit_bfs visit)
{
    int nb_cells = state->board_size * state->board_size;
    bool *seen = (bool *)malloc(nb_cells * sizeof(bool));
    for (int i = 0; i < nb_cells; i++)
        seen[i] = false;
    queue *to_visit = create_queue();
    add_queue(to_visit, state->curr_player->start);
    point p;
    while (!empty_queue(to_visit))
    {
        pop_queue(to_visit, &p);
        (*visit)(&p, seen, to_visit, state, color, val);
    }
    free(to_visit);
    free(seen);
}

void score_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *score)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
        {
            cell_color = state->curr_player->id;
            (*score)++;
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
                    add_queue(to_visit, &voisin);
                }
            }
        }
    }
}

int color_score(State *state, char color)
{
    int score = state->curr_player->score;
    compute_bfs(state, color, &score, score_visit);
    return score;
}

char best_score(State *state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state, reachable);
    char best = 0;
    int score_max = 0;
    char color;
    int score;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            score = color_score(state, color);
            if (score > score_max)
            {
                best = color;
                score_max = score;
            }
        }
    }
    return best;
}

int cell_expansion(point *p, State *state)
{
    int x, y;
    int expansion = 4;
    for (int k = 0; k < 4; k++)
    {
        x = p->x + direction[k].x;
        y = p->y + direction[k].y;
        if (in_bounds(state->board_size, x, y))
        {
            char cell_color = get_cell(state->board, state->board_size, x, y);
            if (cell_color == state->curr_player->id)
                expansion--;
            // blocking the enemy is considered as an expansion
        }
        else
            expansion--;
    }
    return expansion;
}

void perimeter_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *perimeter)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
            cell_color = state->curr_player->id;
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
                    add_queue(to_visit, &voisin);
                }
                else
                    (*perimeter)++;
                // On compte le bord du plateau
            }
        }
        // On ne veut pas prendre en compte les cellules enclavées
        else if (cell_expansion(p, state) > 1)
            (*perimeter)++;
    }
}

int color_perimeter(State *state, char color)
{
    int perimeter = 0;
    compute_bfs(state, color, &perimeter, perimeter_visit);
    return perimeter;
}

char best_perimeter(State *state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state, reachable);
    char best = 0;
    int perimeter_max = 0;
    char color;
    int perimeter;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            perimeter = color_perimeter(state, color);
            if (perimeter > perimeter_max)
            {
                best = color;
                perimeter_max = perimeter;
            }
        }
    }
    return best;
}

void perimeter_borderless_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *perimeter)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
            cell_color = state->curr_player->id;
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
                    add_queue(to_visit, &voisin);
                }
                // On ne compte pas le bord du plateau
            }
        }
        // On ne veut pas prendre en compte les cellules enclavées
        else if (cell_expansion(p, state) > 1)
            (*perimeter)++;
    }
}

int color_perimeter_borderless(State *state, char color)
{
    int perimeter = 0;
    compute_bfs(state, color, &perimeter, perimeter_borderless_visit);
    return perimeter;
}

char best_perimeter_borderless(State *state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state, reachable);
    char best = 0;
    int perimeter_max = 0;
    char color;
    int perimeter;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            perimeter = color_perimeter_borderless(state, color);
            if (perimeter > perimeter_max)
            {
                best = color;
                perimeter_max = perimeter;
            }
        }
    }
    return best;
}

void expansion_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *expansion)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
        {
            cell_color = state->curr_player->id;
            (*expansion)++;
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
                    add_queue(to_visit, &voisin);
                }
                else
                    (*expansion)++;
                // On compte le bord du plateau
            }
        }
        // On ne veut pas prendre en compte les cellules enclavées
        else if (cell_expansion(p, state) > 1)
            (*expansion)++;
    }
}

int color_expansion(State *state, char color)
{
    int expansion = state->curr_player->score;
    compute_bfs(state, color, &expansion, expansion_visit);
    return expansion;
}

char best_expansion(State *state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state, reachable);
    char best = 0;
    int expansion_max = 0;
    char color;
    int expansion;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            expansion = color_expansion(state, color);
            if (expansion > expansion_max)
            {
                best = color;
                expansion_max = expansion;
            }
        }
    }
    return best;
}

void expansion_borderless_visit(point *p, bool *seen, queue *to_visit, State *state, char color, int *expansion)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
        {
            cell_color = state->curr_player->id;
            (*expansion)++;
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
                    add_queue(to_visit, &voisin);
                }
                // On ne compte pas le bord du plateau
            }
        }
        // On ne veut pas prendre en compte les cellules enclavées
        else if (cell_expansion(p, state) > 1)
            (*expansion)++;
    }
}

int color_expansion_borderless(State *state, char color)
{
    int expansion = state->curr_player->score;
    compute_bfs(state, color, &expansion, expansion_borderless_visit);
    return expansion;
}

char best_expansion_borderless(State *state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state, reachable);
    char best = 0;
    int expansion_max = 0;
    char color;
    int expansion;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            expansion = color_expansion_borderless(state, color);
            if (expansion > expansion_max)
            {
                best = color;
                expansion_max = expansion;
            }
        }
    }
    return best;
}

point minimax(State *state, heuristic heur, int depth, int *alpha, int *beta, bool maximizing)
{
    int score_max = state->board_size * state->board_size;
    if (depth == 0 || game_ended(state->player1->score, state->player2->score, score_max))
    {
        point score = {color_id(state->curr_move), (*heur)(state, state->curr_move)};
        return score;
    }
    else
    {
        // recherche des couleurs atteignables
        bool reachable[NB_COLORS] = {false};
        reachable_colors(state, reachable);
        point score;
        point best = {-1, 0};
        if (!maximizing)
            best.y = score_max;
        State *new_state = NULL;
        for (int i = 0; i < NB_COLORS; i++)
        {
            if (reachable[i])
            {
                // on réinitialise new_state
                Player new_player1 = {state->player1->id, state->player1->score, state->player1->start};
                Player new_player2 = {state->player2->id, state->player2->score, state->player2->start};
                state_cpy(&new_state, state, &new_player1, &new_player2);
                // on joue la ième couleur
                new_state->curr_move = colors[i];
                update_board(new_state);
                // on change de joueur
                if (new_state->curr_player->id == new_state->player1->id)
                    new_state->curr_player = new_state->player2;
                else
                    new_state->curr_player = new_state->player1;
                // on simule le meilleur score
                score = minimax(new_state, heur, depth - 1, alpha, beta, !maximizing);
                free_state(new_state);
                // cas 1: on veut maximiser les scores possibles
                if (maximizing && score.y > best.y)
                {
                    best.x = i;
                    best.y = score.y;
                    if (*alpha > best.y)
                        *alpha = best.y;
                }
                // cas 2: on veut minimiser les scores possibles
                else if (!maximizing && score.y < best.y)
                {
                    best.x = i;
                    best.y = score.y;
                    if (*beta < best.y)
                        *beta = best.y;
                }
                if (*alpha >= *beta)
                    break;
            }
        }
        if (best.x == -1)
            // pas de meilleur coup
            best.x = randint(NB_COLORS);
        return best;
    }
}

char harpagon(State *state)
{
    int depth = 4;
    int alpha = 0;
    int beta = state->board_size * state->board_size;
    point best = minimax(state, color_score, depth, &alpha, &beta, true);
    return colors[best.x];
}

char napoleon(State *state)
{
    int depth = 4;
    int alpha = 0;
    int beta = state->board_size * state->board_size;
    point best = minimax(state, color_expansion_borderless, depth, &alpha, &beta, true);
    return colors[best.x];
}

/************ Tests **************/

SUT_TEST(test_reachable_colors)
{
    char board[] = {'1', '1', 'G', 'C', 'J', 'M', 'V', 'B', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 2, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 3, &player1, &player2, &player1, '?', 1};
    bool reachable[NB_COLORS] = {false};
    reachable_colors(&state, reachable);
    bool expected[NB_COLORS] = {false};
    expected[color_id('G')] = expected[color_id('C')] = expected[color_id('J')] = true;
    for (int i = 0; i < NB_COLORS; i++)
        SUT_INT_EQUAL(reachable[i], expected[i], "The color %c is not correctly marked as reachable.", colors[i]);
    return 1;
}

SUT_TEST(test_random_reachable_color)
{
    char board[] = {'1', '1', 'G', 'C', 'J', 'M', 'V', 'B', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 2, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 3, &player1, &player2, &player1, '?', 1};
    char c;
    for (int i = 0; i < 50; i++)
    {
        c = random_reachable_color(&state);
        SUT_ASSERT_TRUE(c == 'G' || c == 'C' || c == 'J', "random_reachable_color returns a color that is not reachable.");
    }
    return 1;
}

SUT_TEST(test_color_score)
{
    char board[] = {
        '1', '1', '1', 'C', 'C',
        'G', 'M', '1', 'V', 'C',
        'J', 'J', 'R', 'V', 'J',
        'J', 'J', 'J', 'J', 'J',
        'J', 'J', 'J', 'J', '2'};
    point start1 = {0, 0}, start2 = {4, 4};
    Player player1 = {PLAYER1, 4, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 5, &player1, &player2, &player1, '?', 1};
    int expected[NB_COLORS];
    expected[color_id('B')] = 4;
    expected[color_id('J')] = 4;
    expected[color_id('G')] = 5;
    expected[color_id('M')] = 5;
    expected[color_id('R')] = 5;
    expected[color_id('V')] = 6;
    expected[color_id('C')] = 7;
    for (int i = 0; i < NB_COLORS; i++)
    {
        SUT_INT_EQUAL(color_score(&state, colors[i]), expected[i], "Le score calculé pour la couleur %c est incorrect.", colors[i]);
    }
    return 1;
}

SUT_TEST(test_best_score)
{
    char board[] = {
        '1', '1', '1', 'C', 'C',
        'G', 'M', '1', 'V', 'C',
        'J', 'J', 'R', 'V', 'J',
        'J', 'J', 'J', 'J', 'J',
        'J', 'J', 'J', 'J', '2'};
    point start1 = {0, 0}, start2 = {4, 4};
    Player player1 = {PLAYER1, 4, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 5, &player1, &player2, &player1, '?', 1};
    char c = best_score(&state);
    SUT_CHAR_EQUAL(c, 'C', "best_score does not return the correct color.");
    return 1;
}

SUT_TEST(test_color_perimeter)
{
    char board[] = {
        '1', '1', '1', 'C', 'C',
        'G', 'M', '1', 'V', 'C',
        'J', 'J', 'R', 'V', 'J',
        'J', 'J', 'J', 'J', 'J',
        'J', 'J', 'J', 'J', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 4, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 5, &player1, &player2, &player1, '?', 1};
    int expected[NB_COLORS];
    expected[color_id('B')] = 9;
    expected[color_id('J')] = 9;
    expected[color_id('M')] = 9;
    expected[color_id('G')] = 10;
    expected[color_id('R')] = 11;
    expected[color_id('V')] = 11;
    expected[color_id('C')] = 13;
    for (int i = 0; i < NB_COLORS; i++)
    {
        SUT_INT_EQUAL(color_perimeter(&state, colors[i]), expected[i], "Le périmètre calculé pour la couleur %c est incorrect.", colors[i]);
    }
    return 1;
}

SUT_TEST(test_best_perimeter)
{
    char board[] = {
        '1', '1', '1', 'C', 'C',
        'G', 'M', '1', 'V', 'C',
        'J', 'J', 'R', 'V', 'J',
        'J', 'J', 'J', 'J', 'J',
        'J', 'J', 'J', 'J', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 4, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 5, &player1, &player2, &player1, '?', 1};
    char c = best_perimeter(&state);
    SUT_CHAR_EQUAL(c, 'C', "best_perimeter does not return the correct color.");
    return 1;
}

SUT_TEST(test_best_perimeter_borderless)
{
    char board[] = {
        '1', '1', '1', 'C', 'C',
        'G', 'M', '1', 'V', 'C',
        'J', 'J', 'R', 'V', 'C',
        'J', 'J', 'J', 'V', 'C',
        'J', 'J', 'J', 'J', '2'};
    point start1 = {0, 0}, start2 = {2, 2};
    Player player1 = {PLAYER1, 4, &start1}, player2 = {PLAYER2, 1, &start2};
    State state = {board, 5, &player1, &player2, &player1, '?', 1};
    char c = best_perimeter_borderless(&state);
    SUT_CHAR_EQUAL(c, 'V', "best_perimeter_borderless does not return the correct color.");
    return 1;
}

SUT_TEST_SUITE(strategies) = {
    SUT_TEST_SUITE_ADD(test_reachable_colors),
    SUT_TEST_SUITE_ADD(test_random_reachable_color),
    SUT_TEST_SUITE_ADD(test_color_score),
    SUT_TEST_SUITE_ADD(test_best_score),
    SUT_TEST_SUITE_ADD(test_color_perimeter),
    SUT_TEST_SUITE_ADD(test_best_perimeter),
    SUT_TEST_SUITE_ADD(test_best_perimeter_borderless),
    SUT_TEST_SUITE_END};
