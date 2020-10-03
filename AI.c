#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "board.h"
#include "game.h"
#include "AI.h"

char random_color()
{
    int n = rand() % NB_COLORS;
    return colors[n];
}

void visit_colors_bfs(point *p, bool *seen, queue *visit, char *possible_colors, int *nb_possible_colors)
{
    char cell_color = get_cell(p->x, p->y);
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        if (cell_color == PLAYER2)
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
        else if (cell_color != PLAYER1)
        {
            bool color_seen = false;
            int i = 0;
            while (i < *nb_possible_colors && !color_seen)
            {
                if (cell_color == possible_colors[i])
                    color_seen = true;
            }
            if (!color_seen)
            {
                possible_colors[*nb_possible_colors] = cell_color;
                (*nb_possible_colors)++;
            }
        }
    }
}

void get_possible_colors_bfs(char *possible_colors, int *nb_possible_colors)
{
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    point *p = (point *)malloc(sizeof(point));
    add_queue(visit, &start2);

    while (!empty_queue(visit) && *nb_possible_colors < NB_COLORS)
    {
        pop_queue(visit, p);
        visit_colors_bfs(p, seen, visit, possible_colors, nb_possible_colors);
    }
    free(p);
    free(visit);
}

void print_possible_colors(char *possible_colors, int nb_possible_colors)
{
    printf("couleurs possibles : ");
    for (int i = 0; i < nb_possible_colors; i++)
    {
        printf("%c ", possible_colors[i]);
    }
    printf("\n");
}

char random_possible_color()
{
    char possible_colors[NB_COLORS];
    int nb_possible_colors = 0;
    printf("1");
    get_possible_colors_bfs(possible_colors, &nb_possible_colors);
    printf("2");
    print_possible_colors(possible_colors, nb_possible_colors);
    printf("3");
    int n = rand() % nb_possible_colors;
    return possible_colors[n];
}

char get_AI_move()
{
    // AI plays randomly
    // return random_possible_color();
    return random_color();
}
