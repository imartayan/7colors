#include "structures.h"

bool empty_list(list head)
{
    return head == NULL;
}

void print_list(list head)
{
    while (!empty_list(head))
    {
        printf("(%d,%d) -> ", head->val.x, head->val.y);
        head = head->next;
    }
    printf("\n");
}

void add_list(list *lst, point *p)
{
    list new = (cell *)malloc(sizeof(cell));
    new->next = *lst;
    new->val = *p;
    *lst = new;
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

    list old = *lst;
    (*lst) = (*lst)->next;
    free(old);
}

void reverse_list(list *src, list *dest)
{
    point *p = (point *)malloc(sizeof(point));
    while (!empty_list(*src))
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

void print_queue(queue *q)
{
    printf("IN: ");
    print_list(q->in);
    printf("OUT: ");
    print_list(q->out);
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
