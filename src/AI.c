#include "AI.h"

char play_random_color(char player)
{
    return random_color();
}

void reachable_color_bfs(point *p, bool *seen, queue *visit, char player, bool *reachable)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(p->x, p->y);
        if (cell_color == player)
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

void reachable_colors(char player, bool *reachable)
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
        reachable_color_bfs(p, seen, visit, player, reachable);
    }
    free(p);
    free(visit);
}

char random_reachable_color(char player)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(player, reachable);
    int count = count_true(reachable, NB_COLORS);
    int n = 1 + randint(count);
    return colors[get_nth_true(reachable, NB_COLORS, n)];
}

void simulate_color_bfs(point *p, bool *seen, queue *visit, char player, char color, int *score)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(p->x, p->y);
        if (cell_color == color)
        {
            cell_color = player;
            (*score)++;
        }
        if (cell_color == player)
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

int simulate_color(char player, char color)
{
    int score = 0;
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
        simulate_color_bfs(p, seen, visit, player, color, &score);
    }
    free(p);
    free(visit);
    return score;
}

char best_reachable_color(char player)
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
            score = simulate_color(player, color);
            if (score > score_max)
            {
                best = color;
                score_max = score;
            }
        }
    }
    return best;
}
