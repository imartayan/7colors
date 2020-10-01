#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "board.h"

bool empty_list(list head)
{
    return head == NULL;
}

void add_list(list *lst, point *p)
{
    list head = *lst;
    list new = (cell *)malloc(sizeof(cell));
    lst = &new;
    new->next = head;
    new->val.x = p->x;
    new->val.y = p->y;
}

void pop_list(list *lst, point *p)
{
    if (empty_list(*lst))
    {
        fprintf(stderr, "impossible de retirer la t%cte d'une liste vide", 136);
        exit(69);
    }

    p->x = (*lst)->val.x;
    p->y = (*lst)->val.y;

    if ((*lst)->next == NULL)
        (*lst) = NULL;
    else
        (*lst)->next = (*lst)->next->next;
    free(*lst);
}

void reverse_list(list *src, list *dest)
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
    return q;
}

bool empty_queue(queue *q)
{
    return (empty_list(q->in) && empty_list(q->out));
}

void add_queue(queue *q, point *p)
{
    add_list(&(q->in), p);
}

void pop_queue(queue *q, point *p)
{
    if (empty_queue(q))
    {
        fprintf(stderr, "impossible de retirer un %cl%cment d'une file vide", 233, 233);
        exit(42);
    }
    if (empty_list(q->out))
        reverse_list(&q->in, &q->out);
    pop_list(&q->out, p);
}
