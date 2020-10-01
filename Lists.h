#ifndef LISTS_H
#define LISTS_H

typedef struct cell
{
    point val;
    struct cell *next;
} cell;

bool empty_list(cell *head);
void add_list(cell **head, point *p);
void pop_list(cell **head, point *p);
void reverse_list(cell **src, cell **dest);

typedef struct queue
{
    cell *in;
    cell *out;
} queue;

bool empty_queue(queue *q);
queue *create_queue();
void add_queue(queue **q, point *p);
void pop_queue(queue **q, point *p);

#endif
