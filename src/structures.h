#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

typedef struct point
{
    int x;
    int y;
} point;

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

typedef char (*strategy)(State *);

typedef struct cell
{
    point val;
    struct cell *next;
} cell;

typedef cell *list;

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
