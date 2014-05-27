#include "link.h"

#define SENTINELLE_TETE '\0'

struct lelement
{
  void *data;
  struct lelement *next;
};

struct link
{
  struct lelement *head;
  struct lelement *tail;
};


void lnk__empty(struct link *l)
{
  l->head = NULL;
}


int lnk__find(struct link *l, int id)
{
  struct lelement *tmp;
  for(tmp = l->head; !lnk__is_end_mark(tmp); tmp = tmp->next)
    if (vertex_get_id((struct vertex*) tmp->data) == id)
	      return 1;
  return 0;
}




int lnk__is_end_mark(struct lelement *e)
{
  return (e == NULL);
}

void lnk__add_head(struct link *l, struct lelement *e)
{
  e->next = l->head;
  l->head = e;
}

struct lelement *lnk__remove_head(struct link *l)
{
  assert(!lnk__is_end_mark(l->head));
  struct lelement *tmp = l->head;
  l->head = l->head->next;
  return tmp;
}

void lnk__add_after(struct lelement *e, struct lelement *f)
{
  if(!lnk__is_end_mark(e))
    {
      struct lelement *tmp = e->next;
      e->next = f;
      f->next = tmp;
    }
}
    

struct lelement *lnk__remove_after(struct lelement *e)
{
  assert(!lnk__is_end_mark(e->next));
  struct lelement *tmp = e->next;
  e->next = e->next->next;
  return tmp;
}


void lnk__add_tail(struct link *l, struct lelement *e)
{
  l->tail->next = e;
  l->tail = e;
}

struct lelement *lnk__remove_tail(struct link *l)
{
  struct lelement *tmp2 = l->tail;
  struct lelement *tmp;
  for(tmp = l->head; !lnk__is_end_mark(tmp->next->next); tmp = tmp->next);
  l->tail = tmp;
  return tmp2;
}
    
    




int lnk__are_disjoint(const struct link *l1, const struct link *l2)
{
  struct lelement *tmp = NULL;
  struct lelement *tmp2 = NULL;
  
  for (tmp = l1->head; tmp != NULL; tmp = tmp->next)
    for(tmp2 = l2->head; tmp2 != NULL; tmp2 = tmp2->next)
      if(tmp2->data == tmp->data)
	return 0;
  return 1;
}


void lnk__free(struct link *l)
{
  struct lelement *rm;
  struct lelement *tmp;
  for (rm= l->head; rm != NULL; rm = tmp)
    {
      tmp = rm->next;
      free(rm);
    }
  free(tmp);
  free(l);
}
  
