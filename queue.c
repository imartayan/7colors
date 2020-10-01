#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "queue.h"

bool empty_list(cell *head)
{
    return head == NULL;
}

void add_list(cell **head, point *p)
{
    cell *old = *head;
    cell *new = (cell *)malloc(sizeof(cell));
    head = &new;
    new->next = old;
    new->val.x = p->x;
    new->val.y = p->y;
}

void pop_list(cell **head, point *p)
{
    if (empty_list(*head))
    {
        fprintf(stderr, "impossible de retirer la t%cte d'une liste vide", 136);
        exit(69);
    }
    p->x = (*head)->val.x;
    p->y = (*head)->val.y;

    if ((*head)->next == NULL)
        (*head) = NULL;
    else
        (*head)->next = (*head)->next->next;
    free(**head);
}

void reverse_list(cell **src, cell **dest)
{
    point *p = (point *)malloc(sizeof(point));
    while (*src != NULL)
    {
        pop_list(src, p);
        add_list(dest, p);
    }
    free(p);
}

queue *create_queue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->in = NULL;
    q->out = NULL;
}

bool empty_queue(queue *q)
{
    return (empty_list(q->in) && empty_list(q->out));
}

void add_queue(queue **q, point *p)
{
    add_list(&((*q)->in), p);
}

void pop_queue(queue **q, point *p)
{
    if (empty_queue(*q))
    {
        fprintf(stderr, "impossible de retirer un %cl%cment d'une file vide", 233, 233);
        exit(42);
    }
    if (empty_list((*q)->out))
        reverse_list(&(*q)->in, &(*q)->out);
    pop_list((*q)->out, p);
}
