#include <vectorSolver/solver.h>

struct node
{
  int x,y,dx,dy;
  struct node * parent;
};

void init_src(struct map * map, struct node * src)
{
  for(int i = 0; i<map->w;i++)
    {
      for(int j = 0; j<map->h; j++)
	{
	  if(map->grid[i][j] == '*')
	    {
	      src->x = i;
	      src->y = j;
	    }
	}
    }
  src->dx = 0;
  src->dy = 0;
  src->parent = NULL;
}


struct node * generate_successor(struct map * map, struct node * item, int i, int j)
{
  if((item->x + item->dx + i < map->w) && (item->x + item->dx + i >= 0) && (item->y + item->dy + j < map->h) && (item->y + item->dy + j >= 0) && (isdigit(map->grid[item->x + item->dx + i][item->y + item->dy + j]) || map->grid[item->x + item->dx + i][item->y + item->dy + j] == '*') && ((item->dx + i != 0) || (item->dy + j != 0)))
    {
      struct node * successor = (struct node *)malloc(sizeof(struct node));
      successor->x = item->x + item->dx + i;
      successor->y = item->y + item->dy + j;
      successor->dx = item->dx + i;
      successor->dy = item->dy + j;
      successor->parent = item;
      return successor;
    }
  return NULL;
}


struct list * generate_successors(struct map * map, struct node * item)
{
  struct list * successors = list_empty();
  struct node * tmp = NULL;
  if((tmp = generate_successor(map,item,0,0)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,1,0)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,-1,0)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,0,1)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,0,-1)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,-1,1)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,1,-1)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,1,1)) != NULL)
    list_add(successors,tmp);
  if((tmp = generate_successor(map,item,-1,-1)) != NULL)
    list_add(successors,tmp);
  return successors;
}
 
int zone_found(struct map * map, char c)
{
  for(int i = 0; i<map->w; i++)
    {
      for(int j = 0; j<map->h; j++)
	{
	  if(map->grid[i][j] == c)
	    return 1;
	}
    }
  return 0;
}


char * identify_zones(struct map * map)
{
  int i = 1;
  char * map_zones = (char *)malloc(MAX_ZONES*sizeof(char));
  map_zones[0] = '*';
  for(i = 1; i<=9; i++)
    {
      if(zone_found(map,i+'0'))
	map_zones[i] = i + '0';
      else
	map_zones[i] = 'x';
    }
  map_zones[MAX_ZONES - 1] = 0;
  return map_zones;
}

int number_of_zones(char * map_zones)
{
  int j = 0;
  for(int i = 0; i<MAX_ZONES-2; i++)
    {
      if(map_zones[i] != 'x')
	j++;
    }
  return j;
}


int valid_path(struct map * map, struct node * current, char * map_zones)
{
  printf("testing valid path\n");
  struct node * tmp = current;
  char c;
  while(tmp != NULL)
    {
      c = map->grid[tmp->x][tmp->y];
      if(c == '*')
	map_zones[0] = 'x';
      else
	map_zones[c-'0'] = 'x';
      tmp = tmp->parent;
    }
  for(int i = 0; i<MAX_ZONES-1;i++)
    {
      if(map_zones[i] != 'x')
      	{
      	  printf("test failed because %d not in path\n",i);
      	  return 0;
      	}
    }
  return 1;
}


int not_colored(struct list * colored, struct node * successor)
{
  struct lelement * tmp = colored->head;
  while(tmp != NULL)
    {
      if((successor->x == ((struct node *)(tmp->data))->x) && (successor->y == ((struct node *)(tmp->data))->y) && (successor->dx == ((struct node *)(tmp->data))->dx) && (successor->dy == ((struct node *)(tmp->data))->dy))
	return 0;
      tmp = tmp->next;
    }
  return 1;
}


struct list * find_path(struct map * map, struct node * src)
{
  struct list * queue = list_empty();
  struct list * colored = list_empty();
  struct list * trash = list_empty();
  struct list * solution = list_empty();
  struct list * successors = NULL;
  struct lelement * tmp = NULL;
  struct node * item = NULL;
  char * map_zones = identify_zones(map);
  list_add(trash,src);
  list_add(queue,src);
  while(!list_is_empty(queue))
    {
      item = queue->tail->data;
      list_remove(queue,queue->tail->data);
      list_add(colored,item);
      successors = generate_successors(map,item);
      tmp = successors->head;
      while(tmp != NULL)
	{
	  if(map->grid[((struct node *)(tmp->data))->x][((struct node *)(tmp->data))->y] == '*')
	    {
	      if(valid_path(map,tmp->data,map_zones))
	      	{
	      	  struct node * tmp2 = tmp->data;
		  while(tmp2 != NULL)
		    {
		      printf("(%d %d),,(%d %d)\n",tmp2->x,tmp2->y,tmp2->dx,tmp2->dy);
		      list_add(solution,tmp2);
		      tmp2= tmp2->parent;
		    }
		  list_free_lelement(colored);
		  list_free(queue);
		  list_free(trash);
		  free(map_zones);
	      	  return solution;
	      	}
	    }
	  if(not_colored(colored,tmp->data))
	    list_add(queue,tmp->data);
	  else
	    list_add(trash,tmp->data);
	  tmp = tmp->next;
	}
      list_free_lelement(successors);
    }
  list_free_lelement(colored);
  list_free(queue);
  list_free(trash);
  free(map_zones);
  printf("not found\n");
  return solution;
}



struct list * solve(char * filename)
{
  struct map * map = vector_map_load(filename);
  struct node * src = (struct node *)malloc(sizeof(struct node));
  init_src(map,src);
  return find_path(map,src);
}
