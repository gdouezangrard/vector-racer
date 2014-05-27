#include <vectorDll/vector_dll.h>

struct list * list_empty()
{
  struct list * list = (struct list *)malloc(sizeof(struct list));
  list->head = NULL; 
  list->tail = NULL;
  list->count = 0;
  return list;
}

int list_is_empty(struct list * list)
{
  if(list->head == NULL)
    return 1;
  return 0;
}

void list_add(struct list * list, void * value)
{
  struct lelement * elmt = (struct lelement *)malloc(sizeof(struct lelement));
  elmt->data = value;
  if (list_is_empty(list))
  {
    list->head = elmt;
    list->tail = elmt;
    elmt->prev = NULL;
    elmt ->next = NULL;
  }
  else
  {
    list->tail->next = elmt;
    elmt->prev = list->tail;
    list->tail = elmt;
    list->tail->next = NULL;
  }
}

void list_remove(struct list * list, void * value)
{
  struct lelement * elmt = list->head;
  while(elmt != NULL && elmt->data != value)
  {
    elmt = elmt->next;
  }
  if(elmt != NULL)
  {
    if(elmt == list->head)
    {
      list->head = elmt->next;
      //free(elmt);
    }
    else if(elmt == list->tail)
    {
      list->tail = elmt->prev;
      list->tail->next = NULL;
      //free(elmt);
    }
    else
    {
      elmt->prev->next = elmt->next;
      elmt->next->prev = elmt->prev;
      //free(elmt);
    }
  }
}

void list_print(struct list * list)
{
  struct lelement * tmp = list->head;
  while(tmp != NULL)
  {
    printf("%s\n",(char *)tmp->data);
    tmp = tmp->next;
  }
}

struct list *list_concatenate(struct list * l1, struct list * l2)
{
  struct lelement * tmp = l2->head;
  while(tmp != NULL)
    {
      list_add(l1,tmp->data);
      tmp = tmp->next;
    }
  return l1;
}

void list_print_point (struct list *list)
{
  struct lelement * tmp = list->head;
  while(tmp != NULL)
  {
    // printf("%d.%d -> \n",(int *)tmp->data->x,(int *)tmp->data->y); // Cannot be dereferenced, so each data type must implements its own printing function !
    tmp = tmp->next;
  }
}

void list_free(struct list * list)
{
  struct lelement * tmp = list->head;
  struct lelement * tmp2 = tmp;
  while(tmp != NULL)
    {
      tmp = tmp2->next;
      //free(tmp2->data);
      free(tmp2);
      tmp2 = tmp;
    }
  free(list);
}

void list_add_head(struct list * list, void * value)
{
  struct lelement * elmt = (struct lelement *)malloc(sizeof(struct lelement));
  elmt->data = value;
  if(list_is_empty(list))
  {
    list->head = elmt;
    list->tail = elmt;
    elmt->prev = NULL;
    elmt ->next = NULL;
  }
  else
  {
    elmt->next = list->head;
    elmt->prev = NULL;
    list->head->prev = elmt;
    list->head = elmt;
  }
}

struct list * list_reverse(struct list * list)
{
  struct lelement * tmp = NULL; 
  struct lelement * current = list->head;   
  while (current !=  NULL)
    {
       tmp = current->prev;
       current->prev = current->next;
       current->next = tmp;             
       current = current->prev;
    }     
  if(tmp != NULL )
    list->head = tmp->prev;
  return list;
}

void list_remove_all(struct list * list)
{
  struct lelement * tmp = list->head;
  while(tmp != NULL)
    {
      list_remove(list,tmp->data);
      tmp = tmp->next;
    }
}

void list_free_lelement(struct list * list)
{
  struct lelement * tmp = list->head;
  struct lelement * tmp2 = tmp;
  while(tmp != NULL)
    {
      tmp = tmp2->next;
      free(tmp2);
      tmp2 = tmp;
    }
  free(list);
}
