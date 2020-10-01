#ifndef QUEUE_H
#define QUEUE_H

typedef struct point
{
    int x;
    int y;
} point;

typedef struct cell
{
    point val;
    struct cell *next;
} cell;

typedef cell *list;

bool empty_list(list head);
void add_list(list *head, point *p);
void pop_list(list *head, point *p);
void reverse_list(list *src, list *dest);

typedef struct queue
{
    list in;
    list out;
} queue;

bool empty_queue(queue *q);
queue *create_queue();
void add_queue(queue *q, point *p);
void pop_queue(queue *q, point *p);

#endif
