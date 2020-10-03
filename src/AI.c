#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "structures.h"
#include "board.h"
#include "game.h"
#include "AI.h"
#include "display.h"

void visit_colors_bfs(char* board, point *p, bool *seen, queue *visit, char *possible_colors, int *nb_possible_colors)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(board, p->x, p->y);
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
                else
                    i++;
            }
            if (!color_seen)
            {
                possible_colors[*nb_possible_colors] = cell_color;
                (*nb_possible_colors)++;
            }
        }
    }
}

void get_possible_colors_bfs(char* board, char *possible_colors, int *nb_possible_colors)
{
    bool seen[BOARD_SIZE * BOARD_SIZE] = {false};
    queue *visit = create_queue();
    point *p = (point *)malloc(sizeof(point));
    add_queue(visit, &start2);

    while (!empty_queue(visit) && *nb_possible_colors < NB_COLORS)
    {
        pop_queue(visit, p);
        visit_colors_bfs(board, p, seen, visit, possible_colors, nb_possible_colors);
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

char random_possible_color(char* board)
{
    char possible_colors[NB_COLORS];
    int nb_possible_colors = 0;
    get_possible_colors_bfs(board, possible_colors, &nb_possible_colors);
    print_possible_colors(possible_colors, nb_possible_colors);
    int n = rand() % nb_possible_colors;
    return possible_colors[n];
}

void hegemonic_visit_bfs(char* board, point *p, bool *seen, queue *visit, char color, int *score){
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char curr_cell = get_cell(board, p->x, p->y);
        if (curr_cell == color)
        {
            set_cell(board, p->x, p->y, PLAYER2);
            curr_cell = PLAYER2;
        }
        if (curr_cell == PLAYER2)
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
        if(curr_cell != PLAYER2 && curr_cell != PLAYER1){
          (*score)++;
        }

    }
}

void hegemonic_update_board_bfs(char* board, char color, int *score){
    bool seen[NB_CASES] = {false};
    queue *visit = create_queue();
    add_queue(visit, &start2);
    point *p = (point *)malloc(sizeof(point));
    while (!empty_queue(visit))
    {
        pop_queue(visit, p);
        hegemonic_visit_bfs(board, p, seen, visit, color, score);
    }
    free(p);
    free(visit);
}


char hegemonic_AI(char* board){
  char c;
  int score;
  char board_cpy[NB_CASES];
  // si a la fin de l'execution on a encore maximizer == '?' on aura détecté une erreur
  char maximizer = '?';
  int max = 0;
  for(int i = 0; i < NB_COLORS; i++){
    // on réinitialise le plateau de test à l'état actuel du plateau
    score = 0;
    c = colors[i];
    memcpy(board_cpy, board, NB_CASES);
    hegemonic_update_board_bfs(board_cpy, c, &score);
    if(score > max){
      max = score;
      maximizer = c;
    }
    printf("couleur %c score %d \n", c, score);
  }
  printf("maximizer : %c\n", maximizer);
  return maximizer;
}

char get_AI_move(char* board)
{
    // AI plays randomly
    // return random_color(board);
    // AI plays a random color from thoses adjacent to it's zone
    //return random_possible_color(board);
    // AI plays the color that maximizes the perimeter of it's zone
    return hegemonic_AI(board);
}
