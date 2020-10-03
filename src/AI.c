#include "AI.h"

void reachable_color_bfs(point *p, bool *seen, queue *visit, char player, bool *reachable)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char color = get_cell(p->x, p->y);
        if (color == player)
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
            int i = color_id(color);
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

char random_reachable_color()
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(PLAYER2, reachable);
    int count = count_true(reachable, NB_COLORS);
    int n = 1 + randint(count);
    return colors[get_nth_true(reachable, NB_COLORS, n)];
}
