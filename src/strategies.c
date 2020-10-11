#include <stdlib.h>
#include <stdio.h>
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

char get_minimax(pstate state){
  return (char)minimax(state, 0, true, state->curr_player->id);
}

int minimax(pstate state, int depth, bool maximizing_Player, char player_id){
  int nb_cases = (state->board_size * state->board_size);
  // copie des joueurs
  char player1_id = state->player1->id;
  char player2_id = state->player2->id;
  point player1_start = {state->player1->start->x, state->player1->start->y};
  point player2_start = {state->player2->start->x, state->player2->start->y};
  Player new_player1 = {player1_id, state->player1->score, &player1_start};
  Player new_player2 = {player2_id, state->player2->score, &player2_start};
  // copie de l'état du jeu
  pstate new_state = NULL;
  state_cpy(&new_state, state, &new_player1, &new_player2);

  // mise à jour du plateau
  if(depth > 0)
    update_board(new_state, new_state->curr_move);

  // condition d'arrêt de la réccurence
  if(game_ended(new_state->player1->score, new_state->player2->score, nb_cases) || depth >= MAX_DEPTH){
    int score;
    if(player_id == player1_id)
      score = state->player1->score;
    else
      score = state->player2->score;
    free_state(new_state);
    return score;
  }

  // récuppérer les couleurs jouables pour ne pas lancer de gros calculs sur des couleurs où l'on sait qu'on n'avancera pas
  bool reachable[NB_COLORS] = {false};
  reachable_colors(new_state, reachable);
  int max_score = new_state->curr_player->score;
  int min_score = nb_cases;
  int indice_max = -1;
  for(int i = 0; i < NB_COLORS; i++){
    if(reachable[i]){
      new_state -> curr_move = colors[i];
      if(state->curr_player->id == player1_id)
        new_state->curr_player = new_state->player2;
      else
        new_state->curr_player = new_state->player1;
      int score_i = minimax(new_state, depth+1, !maximizing_Player, player_id);
      if(score_i > max_score){
        max_score = score_i;
        indice_max = i;
      }
      if(score_i < min_score)
        min_score = score_i;
    }
  }
  free_state(new_state);
  if(indice_max == -1){
    printf("erreur");
    return (int)'R';
  }
  if(depth == 0)
    return (int)colors[indice_max];
  if(maximizing_Player)
    return max_score;
  return min_score;
}

char get_minimax_pruning(pstate state){
  int alpha = 0;
  int beta = state->board_size * state->board_size;
  return (char)alpha_beta_pruning_minimax(state, 0, true, state->curr_player->id, &alpha, &beta);
}

int alpha_beta_pruning_minimax(pstate state, int depth, bool maximizing_Player, char player_id, int* alpha, int* beta){
  int nb_cases = (state->board_size * state->board_size);
  // copie des joueurs
  char player1_id = state->player1->id;
  char player2_id = state->player2->id;
  point player1_start = {state->player1->start->x, state->player1->start->y};
  point player2_start = {state->player2->start->x, state->player2->start->y};
  Player new_player1 = {player1_id, state->player1->score, &player1_start};
  Player new_player2 = {player2_id, state->player2->score, &player2_start};
  // copie de l'état du jeu
  pstate new_state = NULL;
  state_cpy(&new_state, state, &new_player1, &new_player2);

  // mise à jour du plateau
  if(depth > 0)
    update_board(new_state, new_state->curr_move);

  // condition d'arrêt de la réccurence
  if(game_ended(new_state->player1->score, new_state->player2->score, nb_cases) || depth >= MAX_DEPTH_PRUNING){
    int score;
    if(player_id == player1_id)
      score = state->player1->score;
    else
      score = state->player2->score;
    free_state(new_state);
    return score;
  }

  // récuppérer les couleurs jouables pour ne pas lancer de gros calculs sur des couleurs où l'on sait qu'on n'avancera pas
  bool reachable[NB_COLORS] = {false};
  reachable_colors(new_state, reachable);
  int max_score = new_state->curr_player->score;
  int min_score = nb_cases;
  int indice_max = 0;
  for(int i = 0; i < NB_COLORS; i++){
    if(reachable[i]){
      new_state -> curr_move = colors[i];
      if(state->curr_player->id == player1_id)
        new_state->curr_player = new_state->player2;
      else
        new_state->curr_player = new_state->player1;
      int score_i = alpha_beta_pruning_minimax(new_state, depth+1, !maximizing_Player, player_id, alpha, beta);
      if(score_i > max_score){
        max_score = score_i;
        indice_max = i;
        if(*alpha > max_score)
          *alpha = max_score;
      }
      if(score_i < min_score){
        min_score = score_i;
        if(*beta < min_score)
          *beta = min_score;
      }
      if(*alpha >= *beta)
        break;
    }
  }
  free_state(new_state);
  if(depth == 0)
    return (int)colors[indice_max];
  if(maximizing_Player)
    return max_score;
  return min_score;
}
