#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "simple_unit_test.h"

bool equal_points(point *p1, point *p2)
{
    return ((p1->x == p2->x) && (p1->y == p2->y));
}

void state_cpy(State **dest, State *src, Player *new_player1, Player *new_player2)
{
    int nb_cases = src->board_size * src->board_size;
    (*dest) = (State *)malloc(sizeof(State));
    (*dest)->board = (char *)malloc(nb_cases * sizeof(char));
    memcpy((*dest)->board, src->board, nb_cases);
    (*dest)->board_size = src->board_size;
    (*dest)->curr_move = src->curr_move;
    (*dest)->player1 = new_player1;
    (*dest)->player2 = new_player2;
    // on a posé comme condition que les id des deux joueurs sont différents ce qui nous donne une condition suffisante pour les différencier
    if (src->curr_player->id == src->player1->id)
        (*dest)->curr_player = new_player1;
    else
        (*dest)->curr_player = new_player2;
}

void free_state(State *state)
{
    free(state->board);
    free(state);
}

bool empty_list(list head)
{
    return head == NULL;
}

bool equal_lists(list list1, list list2)
{
    list curr_list1 = list1;
    list curr_list2 = list2;
    while (!empty_list(curr_list1) && !empty_list(curr_list2))
    {
        if (!equal_points(&(curr_list1->val), &(curr_list2->val)))
            return false;
        curr_list1 = curr_list1->next;
        curr_list2 = curr_list2->next;
    }
    if ((empty_list(curr_list1) && !empty_list(curr_list2)) || (!empty_list(curr_list1) && empty_list(curr_list2)))
        return false;
    return true;
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
        fprintf(stderr, "impossible de retirer la tête d'une liste vide");
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
    point p;
    while (!empty_list(*src))
    {
        pop_list(src, &p);
        add_list(dest, &p);
    }
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
        fprintf(stderr, "impossible de retirer un élément d'une file vide");
        exit(42);
    }
    if (empty_list(q->out))
        reverse_list(&q->in, &q->out);
    pop_list(&q->out, p);
}

/************ Tests **************/

SUT_TEST(test_equal_points)
{
    point p1 = {0, 0};
    point p2 = {0, 0};
    point p3 = {0, 1};
    point p4 = {1, 0};
    point p5 = {1, 1};
    SUT_ASSERT_TRUE(equal_points(&p1, &p2), "two equal points weren't caracterized so by the equal_points function");
    SUT_ASSERT_FALSE(equal_points(&p1, &p3), "two different points were caracterized as equal");
    SUT_ASSERT_FALSE(equal_points(&p1, &p4), "two different points were caracterized as equal");
    SUT_ASSERT_FALSE(equal_points(&p1, &p5), "two different points were caracterized as equal");
    return 1;
}

SUT_TEST(test_equal_lists)
{
    point points[] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}};
    point pfree;
    list lst1 = NULL;
    list lst2 = NULL;
    list lst3 = NULL;
    list lst4 = NULL;
    SUT_ASSERT_TRUE(equal_lists(lst1, lst2), "two empty lists weren't caracterized as equal");
    for (int i = 0; i < 4; i++)
    {
        add_list(&lst1, &(points[i]));
        add_list(&lst2, &(points[i]));
        add_list(&lst3, &(points[i]));
    }
    add_list(&lst3, &(points[4]));
    add_list(&lst4, &(points[0]));
    add_list(&lst4, &(points[2]));
    add_list(&lst4, &(points[3]));
    add_list(&lst4, &(points[1]));
    SUT_ASSERT_TRUE(equal_lists(lst1, lst2), "two equal lists weren't caracterized so");
    SUT_ASSERT_FALSE(equal_lists(lst1, lst3), "two lists with the first few numbers equal but not the same number of elements were caracterized as equal");
    SUT_ASSERT_FALSE(equal_lists(lst1, lst4), "two lists cotaining the same elements but not in the same oder were caracterized as equal");
    // free the memory
    for (int i = 0; i < 4; i++)
    {
        pop_list(&lst1, &pfree);
        pop_list(&lst2, &pfree);
        pop_list(&lst3, &pfree);
        pop_list(&lst4, &pfree);
    }
    pop_list(&lst3, &pfree);
    return 1;
}

SUT_TEST(test_empty_list)
{
    list lst = NULL;
    SUT_ASSERT_TRUE(empty_list(lst), "an empty list wasn't caracterized so by the empty_list function");
    point p = {0, 0};
    add_list(&lst, &p);
    SUT_ASSERT_FALSE(empty_list(lst), "a non empty list was caracterized empty by the empty_list function");
    // free the memory
    pop_list(&lst, &p);
    return 1;
}

SUT_TEST(test_add_list)
{
    list lst = NULL;
    point p1 = {0, 0};
    point ptest = {0, 0};
    add_list(&lst, &p1);
    SUT_ASSERT_TRUE(equal_points(&(lst->val), &ptest), "the first point in the list isn't equal to the point we added");
    // free the memory
    pop_list(&lst, &p1);
    return 1;
}

SUT_TEST(test_pop_list)
{
    list lst = NULL;
    point p1 = {0, 0};
    point p2 = {1, 2};
    point ptest;
    add_list(&lst, &p1);
    add_list(&lst, &p2);
    pop_list(&lst, &ptest);
    SUT_ASSERT_TRUE(equal_points(&p2, &ptest), "the point poped off of the list isn't equal to the last point we added");
    // free the memory
    pop_list(&lst, &ptest);
    return 1;
}

SUT_TEST(test_reverse_list)
{
    point points[] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {1, 2}};
    point p;
    list lst1 = NULL;
    list lst2 = NULL;
    list revlst1 = NULL;
    for (int i = 0; i < 5; i++)
    {
        add_list(&lst1, &(points[i]));
        add_list(&lst2, &(points[4 - i]));
    }
    reverse_list(&lst1, &revlst1);
    SUT_ASSERT_TRUE(equal_lists(revlst1, lst2), "the reversed list isn't equal to the list with elements added in the opposite order");
    // free the memory
    for (int i = 0; i < 5; i++)
    {
        pop_list(&revlst1, &p);
        pop_list(&lst2, &p);
    }
    return 1;
}

SUT_TEST(test_empty_queue)
{
    queue *q = create_queue();
    point p = {0, 0};
    SUT_ASSERT_TRUE(empty_queue(q), "an empty queue wasn't caracterized so by the empty_queue function");
    add_queue(q, &p);
    SUT_ASSERT_FALSE(empty_queue(q), "a non empty queue wasn't caracterized so by the empty_queue function");
    // free the memory
    pop_queue(q, &p);
    return 1;
}

SUT_TEST(test_add_queue)
{
    queue *q = create_queue();
    list lst = NULL;
    point p1 = {0, 0};
    point p2 = {1, 0};
    add_queue(q, &p1);
    add_list(&lst, &p1);
    add_queue(q, &p2);
    add_list(&lst, &p2);
    SUT_ASSERT_TRUE(equal_lists(lst, (q->in)), "the queue's in list isn't equal to a list created with the same elements il the same order");
    // free the memory
    pop_queue(q, &p1);
    pop_queue(q, &p1);
    pop_list(&lst, &p1);
    pop_list(&lst, &p2);
    return 1;
}

SUT_TEST(test_pop_queue)
{
    queue *q = create_queue();
    point p1 = {0, 0};
    point p2 = {1, 0};
    point ptest;
    add_queue(q, &p1);
    add_queue(q, &p2);
    pop_queue(q, &ptest);
    SUT_ASSERT_TRUE(equal_points(&ptest, &p1), "the first element inserted in the queue isn't the first out");
    // free the memory
    pop_queue(q, &ptest);
    return 1;
}

SUT_TEST_SUITE(structures) = {
    SUT_TEST_SUITE_ADD(test_equal_points),
    SUT_TEST_SUITE_ADD(test_equal_lists),
    SUT_TEST_SUITE_ADD(test_empty_list),
    SUT_TEST_SUITE_ADD(test_add_list),
    SUT_TEST_SUITE_ADD(test_pop_list),
    SUT_TEST_SUITE_ADD(test_reverse_list),
    SUT_TEST_SUITE_ADD(test_empty_queue),
    SUT_TEST_SUITE_ADD(test_add_queue),
    SUT_TEST_SUITE_ADD(test_pop_queue),
    SUT_TEST_SUITE_END};
