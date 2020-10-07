#include <stdlib.h>
#include "strategies.h"
#include "defaults.h"
#include "input.h"
#include "utils.h"
#include "board.h"

char play_human_move(Player *player)
{
    return ask_player_move();
}

char play_random_move(Player *player)
{
    return random_color();
}

void reachable_colors_bfs(point *p, bool *seen, queue *visit, Player *player, bool *reachable)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(p->x, p->y);
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
        else
        {
            int i = color_id(cell_color);
            if (i >= 0)
                reachable[i] = true;
        }
    }
}

void reachable_colors(Player *player, bool *reachable)
{
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    add_queue(visit, player->start);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        reachable_colors_bfs(p, seen, visit, player, reachable);
    }
    free(p);
    free(visit);
}

char random_reachable_color(Player *player)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(player, reachable);
    int count = count_true(reachable, NB_COLORS);
    int n = 1 + randint(count);
    return colors[get_nth_true(reachable, NB_COLORS, n)];
}

void color_score_bfs(point *p, bool *seen, queue *visit, Player *player, char color, int *score)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(p->x, p->y);
        if (cell_color == color)
        {
            cell_color = player->id;
            (*score)++;
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

int color_score(Player *player, char color)
{
    int score = 0;
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    add_queue(visit, player->start);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        color_score_bfs(p, seen, visit, player, color, &score);
    }
    free(p);
    free(visit);
    return score;
}

char best_score(Player *player)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(player, reachable);
    char best = 0;
    int score_max = 0;
    char color;
    int score;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            score = color_score(player, color);
            if (score > score_max)
            {
                best = color;
                score_max = score;
            }
        }
    }
    return best;
}

int cell_expansion(point *p, Player *player)
{
    int x, y;
    int expansion = 4;
    for (int k = 0; k < 4; k++)
    {
        x = p->x + direction[k].x;
        y = p->y + direction[k].y;
        if (in_bounds(x, y))
        {
            char cell_color = get_cell(x, y);
            if (cell_color == player->id)
                expansion--;
            // blocking the enemy is considered as an expansion
        }
        else
            expansion--;
    }
    return expansion;
}

void color_perimeter_bfs(point *p, bool *seen, queue *visit, Player *player, char color, int *perimeter)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(p->x, p->y);
        if (cell_color == color)
        {
            cell_color = player->id;
            (*perimeter)++;
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
        else if (cell_expansion(p, player) > 1)
            (*perimeter)++;
    }
}

int color_perimeter(Player *player, char color)
{
    int perimeter = 0;
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    add_queue(visit, player->start);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        color_perimeter_bfs(p, seen, visit, player, color, &perimeter);
    }
    free(p);
    free(visit);
    return perimeter;
}

char best_perimeter(Player *player)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(player, reachable);
    char best = 0;
    int perimeter_max = 0;
    char color;
    int perimeter;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            perimeter = color_perimeter(player, color);
            if (perimeter > perimeter_max)
            {
                best = color;
                perimeter_max = perimeter;
            }
        }
    }
    return best;
}

void color_perimeter_with_border_bfs(point *p, bool *seen, queue *visit, Player *player, char color, int *perimeter)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(p->x, p->y);
        if (cell_color == color)
        {
            cell_color = player->id;
            (*perimeter)++;
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
                else
                    (*perimeter)++;
                // On compte le bord du plateau
            }
        }
        else if (cell_expansion(p, player) > 1)
            (*perimeter)++;
    }
}

int color_perimeter_with_border(Player *player, char color)
{
    int perimeter = 0;
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    add_queue(visit, player->start);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        color_perimeter_with_border_bfs(p, seen, visit, player, color, &perimeter);
    }
    free(p);
    free(visit);
    return perimeter;
}

char best_perimeter_with_border(Player *player)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(player, reachable);
    char best = 0;
    int perimeter_max = 0;
    char color;
    int perimeter;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            perimeter = color_perimeter_with_border(player, color);
            if (perimeter > perimeter_max)
            {
                best = color;
                perimeter_max = perimeter;
            }
        }
    }
    return best;
}
