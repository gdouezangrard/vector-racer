#ifndef DLL_H
#define DLL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vectorMap/read_map.h>

struct lelement
{
  void *data;
  struct lelement *prev;
  struct lelement *next;
};

struct list
{
  struct lelement *head;
  struct lelement *tail;
  int count;
};

struct list *list_empty();
int list_is_empty(struct list *);
void list_add(struct list *, void *);
void list_remove(struct list *, void *);
void list_print(struct list *);
struct list *list_concatenate(struct list *, struct list *);
void list_print_point (struct list *);
void list_free(struct list *);
void list_add_head(struct list *, void *);
struct list * list_reverse(struct list *);
void list_remove_all(struct list *);
void elem_print_data (struct lelement *);
void list_free_lelement(struct list * list);
#endif
