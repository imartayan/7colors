bool test_liste_vide(cell *head){
  return head == NULL;
}

void ajouter_liste(cell** head, point* p){
  cell* new = (cell*) malloc(sizeof(cell));
  cell* old_head = *head;
  head = &new;
  new -> next = old_head;
  new -> val.x = p->x;
  new -> val.y = p->y;
}

void tete(cell **head, point* p){
  if(test_liste_vide(*head)){
    fprintf(stderr, "impossible de retirer la t%cte d'une liste vide", 136);
    exit(69);
  }
   p->x = (*head)->val.x;
   p->y = (*head)->val.y;

   if((*head)->next == NULL)
    (*head) = NULL;
   else
    (*head)->next = (*head)->next->next;
  free(**head);
}

void reverse(cell** src, cell** dest){
  point* p = (point*)malloc(sizeof(point));
  while(*src != NULL){
    tete(src, p);
    ajouter_liste(dest, p);
  }
  free(p);
}

bool empty_queue(queue* q){
  return (test_liste_vide(q->in) && test_liste_vide(q->out));
}

queue* create_queue(){
  queue* q = (queue*)malloc(sizeof(queue));
  q->in = NULL;
  q->out = NULL;
}

void add_queue(queue** q, point* p){
  ajouter_liste(&((*q)->in), p);
}

void pop_queue(queue** q, point* p){
  if (empty_queue(*q)){
    fprintf(stderr, "impossible de retirer un %cl%cment d'une file vide", 233, 233);
    exit(42);
  }
  if(test_liste_vide((*q)->out)
    reverse(&(*q)->in, &(*q)->out);
  tete((*q)->out, p);
}
