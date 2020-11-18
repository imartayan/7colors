#include "AI.h"


void init_state(pstate* new_state, pstate state){
  (*new_state) = (pstate)malloc(sizeof(struct state));
  (*new_state)->board = (char*)malloc(NB_CASES * sizeof(char));
  memcpy((*new_state)->board, state->board, NB_CASES);
  if(state->curr_player == PLAYER2)
    (*new_state)->curr_player = PLAYER1;
  else
    (*new_state)->curr_player = PLAYER2;
  (*new_state)->last_move = state->last_move;
  (*new_state)->score1 = state->score1;
  (*new_state)->score2 = state->score2;
}

void free_state(pstate state){
  free(state->board);
  free(state);
}

bool partie_finie(int score1, int score2){
  return ((score1 > SCORE_MAX / 2) || (score2 > SCORE_MAX / 2));
}

int minimax(pstate state, int depth, bool maximizing_Player, char player){

  pstate new_state = NULL;
  init_state(&new_state, state);
  update_board_bfs(new_state);
  if(partie_finie(new_state->score1, new_state->score2) || depth >= MAX_DEPTH){
    int score;
    if(player == PLAYER1)
      score = state->score1;
    else
      score = state->score2;
    free_state(new_state);
    return score;
  }
  int max_score = 0, min_score = SCORE_MAX;
  for(int i = 0; i < NB_COLORS; i++){
    new_state -> last_move = colors[i];
    if(state->curr_player == PLAYER1)
      new_state->curr_player = PLAYER2;
    else
      new_state->curr_player = PLAYER1;
    int scorei = minimax(new_state, depth+1, !maximizing_Player, player);
    if(scorei > max_score)
      max_score = scorei;
    if(scorei < min_score)
      min_score = scorei;
  }
  free_state(new_state);
  if(maximizing_Player)
    return max_score;
  return min_score;
}

char AI_minimax(pstate state){
  pstate state_cpy = NULL;
  init_state(&state_cpy, state);
  int max_score = 0, indice_max = 0;
  for(int i = 0; i < NB_COLORS; i++){
    state_cpy->last_move = colors[i];
    int color_score = minimax(state_cpy, 1, false, state->curr_player);
    if(color_score > max_score){
      max_score = color_score;
      indice_max = i;
    }
  }
  free(state_cpy);
  return colors[indice_max];
}

int alpha_beta_pruning_minimax(pstate state, int depth, bool maximizing_Player, char player, int* alpha, int* beta){
  pstate new_state = NULL;
  init_state(&new_state, state);
  update_board_bfs(new_state);
  if(partie_finie(new_state->score1, new_state->score2) || depth >= MAX_DEPTH_PRUNING){
    int score;
    if(player == PLAYER1)
      score = state->score1;
    else
      score = state->score2;
    free_state(new_state);
    return score;
  }
  int max_score = 0, min_score = SCORE_MAX;
  for(int i = 0; i < NB_COLORS; i++){
    new_state -> last_move = colors[i];
    if(state->curr_player == PLAYER1)
      new_state->curr_player = PLAYER2;
    else
      new_state->curr_player = PLAYER1;
    int scorei = alpha_beta_pruning_minimax(new_state, depth+1, !maximizing_Player, player, alpha, beta);
    if(scorei > max_score){
      max_score = scorei;
      if(*alpha > max_score)
        *alpha = max_score;
    }
    if(scorei < min_score){
        min_score = scorei;
      if(*beta < min_score)
        *beta = min_score;
    }
    if(*alpha >= *beta)
      break;
  }
  free_state(new_state);
  if(maximizing_Player)
    return max_score;
  return min_score;
}

char AI_alpha_beta_pruning_minimax(pstate state){
  pstate state_cpy = NULL;
  init_state(&state_cpy, state);
  int max_score = 0, indice_max = 0;
  int alpha = 0, beta = SCORE_MAX;
  for(int i = 0; i < NB_COLORS; i++){
    state_cpy->last_move = colors[i];
    int color_score = alpha_beta_pruning_minimax(state_cpy, 1, false, state->curr_player, &alpha, &beta);
    if(color_score > max_score){
      max_score = color_score;
      indice_max = i;
    }
  }
  free(state_cpy);
  return colors[indice_max];
}

void reachable_colors_bfs(char* board, point *p, bool *seen, queue *visit, char player, bool *reachable){
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(board, p->x, p->y);
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

void reachable_colors(char* board, char player, bool *reachable){
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
        reachable_colors_bfs(board, p, seen, visit, player, reachable);
    }
    free(p);
    free(visit);
}

char random_reachable_color(pstate state){
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state->board, state->curr_player, reachable);
    int count = count_true(reachable, NB_COLORS);
    int n = 1 + randint(count);
    return colors[get_nth_true(reachable, NB_COLORS, n)];
}

void color_score_bfs(char* board, point *p, bool *seen, queue *visit, char player, char color, int *score){
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(board, p->x, p->y);
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

int color_score(char* board, char player, char color){
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
        color_score_bfs(board, p, seen, visit, player, color, &score);
    }
    free(p);
    free(visit);
    return score;
}

char best_score(pstate state){
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state->board, state->curr_player, reachable);
    char best = 0;
    int score_max = 0;
    char color;
    int score;
    for (int i = 0; i < NB_COLORS; i++){
        if (reachable[i]){
            color = colors[i];
            score = color_score(state->board, state->curr_player, color);
            if (score > score_max)
            {
                best = color;
                score_max = score;
            }
        }
    }
    return best;
}

int cell_expansion(char* board, point *p, char player){
    int x, y;
    int expansion = 4;
    for (int k = 0; k < 4; k++)
    {
        x = p->x + direction[k].x;
        y = p->y + direction[k].y;
        if (in_bounds(x, y))
        {
            char cell_color = get_cell(board, x, y);
            if (cell_color == player)
                expansion--;
            // blocking the enemy is considered as an expansion
        }
        else
            expansion--;
    }
    return expansion;
}

void color_perimeter_bfs(char* board, point *p, bool *seen, queue *visit, char player, char color, int *perimeter)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(board, p->x, p->y);
        if (cell_color == color)
        {
            cell_color = player;
            (*perimeter)++;
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
        else if (cell_expansion(board, p, player) > 1)
            (*perimeter)++;
    }
}

int color_perimeter(char* board, char player, char color)
{
    int perimeter = 0;
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
        color_perimeter_bfs(board, p, seen, visit, player, color, &perimeter);
    }
    free(p);
    free(visit);
    return perimeter;
}

char best_perimeter(pstate state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state->board, state->curr_player, reachable);
    char best = 0;
    int perimeter_max = 0;
    char color;
    int perimeter;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            perimeter = color_perimeter(state->board, state->curr_player, color);
            if (perimeter > perimeter_max)
            {
                best = color;
                perimeter_max = perimeter;
            }
        }
    }
    return best;
}

void color_perimeter_with_border_bfs(char* board, point *p, bool *seen, queue *visit, char player, char color, int *perimeter)
{
    if (!seen[p->x + p->y * BOARD_SIZE])
    {
        seen[p->x + p->y * BOARD_SIZE] = true;
        char cell_color = get_cell(board, p->x, p->y);
        if (cell_color == color)
        {
            cell_color = player;
            (*perimeter)++;
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
                else
                    (*perimeter)++;
                // On compte le bord du plateau
            }
        }
        else if (cell_expansion(board, p, player) > 1)
            (*perimeter)++;
    }
}

int color_perimeter_with_border(char* board, char player, char color)
{
    int perimeter = 0;
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
        color_perimeter_with_border_bfs(board, p, seen, visit, player, color, &perimeter);
    }
    free(p);
    free(visit);
    return perimeter;
}

char best_perimeter_with_border(pstate state)
{
    bool reachable[NB_COLORS] = {false};
    reachable_colors(state->board, state->curr_player, reachable);
    char best = 0;
    int perimeter_max = 0;
    char color;
    int perimeter;
    for (int i = 0; i < NB_COLORS; i++)
    {
        if (reachable[i])
        {
            color = colors[i];
            perimeter = color_perimeter_with_border(state->board, state->curr_player, color);
            if (perimeter > perimeter_max)
            {
                best = color;
                perimeter_max = perimeter;
            }
        }
    }
    return best;
}
