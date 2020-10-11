#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

typedef struct point
{
    int x;
    int y;
} point;

bool equal_points(point* p1, point* p2);

typedef struct Player
{
    char id;
    int score;
    point *start;
} Player;

typedef struct State
{
    char *board;
    int board_size;
    Player *player1;
    Player *player2;
    Player *curr_player;
    char curr_move;
    int turn;
} State;

typedef State* pstate;

void state_cpy(pstate* dest, pstate src, Player* new_player1, Player* new_player2);
void free_state(pstate state);

typedef char (*strategy)(State *);

typedef struct cell
{
    point val;
    struct cell *next;
} cell;

typedef cell *list;

bool equal_lists(list list1, list list2);
bool empty_list(list head);
void print_list(list head);
void add_list(list *head, point *p);
void pop_list(list *head, point *p);
void reverse_list(list *src, list *dest);

typedef struct queue
{
    list in;
    list out;
} queue;

queue *create_queue();
bool empty_queue(queue *q);
void print_queue(queue *q);
void add_queue(queue *q, point *p);
void pop_queue(queue *q, point *p);

#endif
