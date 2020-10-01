#ifndef LISTS_H
#define LISTS_H

typedef struct cell{
  point val;
  struct cell* next;
}cell;

bool test_liste_vide(cell *head);
void ajouter_liste(cell** head, point* p);
void tete(cell **head, point* p);
void reverse(cell** src, cell** dest);

typedef struct queue{
  cell* in;
  cell* out;
}queue;


bool empty_queue(queue* q);
queue* create_queue();
void add_queue(queue** q, point* p);
void pop_queue(queue** q, point* p);




#endif
