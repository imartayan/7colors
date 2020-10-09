#include <stdlib.h>
#include "strategies.h"
#include "input.h"
#include "utils.h"
#include "board.h"

char play_human_move(State *state)
{
    return ask_player_move();
}

char play_random_move(State *state)
{
    return random_color();
}

void reachable_colors_bfs(point *p, bool *seen, queue *visit, State *state, bool *reachable)
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
                    add_queue(visit, &voisin);
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
    queue *visit = create_queue();
    add_queue(visit, state->curr_player->start);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        reachable_colors_bfs(p, seen, visit, state, reachable);
    }
    free(p);
    free(visit);
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

void color_score_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *score)
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
                    add_queue(visit, &voisin);
                }
            }
        }
    }
}

int color_score(State *state, char color)
{
    int score = 0;
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
        color_score_bfs(p, seen, visit, state, color, &score);
    }
    free(p);
    free(visit);
    free(seen);
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

void color_perimeter_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *perimeter)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
        {
            cell_color = state->curr_player->id;
            (*perimeter)++;
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
        else if (cell_expansion(p, state) > 1)
            (*perimeter)++;
    }
}

int color_perimeter(State *state, char color)
{
    int perimeter = 0;
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
        color_perimeter_bfs(p, seen, visit, state, color, &perimeter);
    }
    free(p);
    free(visit);
    free(seen);
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

void color_perimeter_with_border_bfs(point *p, bool *seen, queue *visit, State *state, char color, int *perimeter)
{
    if (!seen[p->x + p->y * state->board_size])
    {
        seen[p->x + p->y * state->board_size] = true;
        char cell_color = get_cell(state->board, state->board_size, p->x, p->y);
        if (cell_color == color)
        {
            cell_color = state->curr_player->id;
            (*perimeter)++;
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
                else
                    (*perimeter)++;
                // On compte le bord du plateau
            }
        }
        else if (cell_expansion(p, state) > 1)
            (*perimeter)++;
    }
}

int color_perimeter_with_border(State *state, char color)
{
    int perimeter = 0;
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
        color_perimeter_with_border_bfs(p, seen, visit, state, color, &perimeter);
    }
    free(p);
    free(visit);
    free(seen);
    return perimeter;
}

char best_perimeter_with_border(State *state)
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
            perimeter = color_perimeter_with_border(state, color);
            if (perimeter > perimeter_max)
            {
                best = color;
                perimeter_max = perimeter;
            }
        }
    }
    return best;
}
