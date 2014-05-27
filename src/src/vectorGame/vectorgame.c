#include <vectorGame/vectorgame.h>

int game(struct map * map)
{
  int maxcheckpoint = map->maxcheckpoint;
  char checkpoint = '0';
  char cheater = 1;
  int vitx = 0;
  int vity = 0;
  struct list * steps = list_empty();
  struct point * start = (struct point *)malloc(sizeof(struct point));
  start->x = map->D.x;
  start->y = map->D.y;
  list_add(steps, start);

  struct point A;
  struct point B;

  struct lelement * current = steps->head;

  int n = 0;

  void* sdl = vector_SDL_init(map);

  int continuer = 1;
  int k = 0;
  while(continuer && n < 100)
  {
    struct point next;
    vector_SDL_print(map, sdl);

    A.x = ((struct point *)steps->tail->data)->x - 1 + vitx;
    A.y = ((struct point *)steps->tail->data)->y - 1 + vity;
    B.x = A.x + 2;
    B.y = A.y + 2;

    vector_SDL_print_choice(map, sdl, A, B);

    current = steps->head;

    k = 0;
    while(k<n)
    {
      vector_SDL_print_car(map, sdl, *((struct point *)current->data));
      vector_SDL_print_line(map, sdl, *((struct point *)current->data), *((struct point *)current->next->data));
      current = current->next;
      k++;
    }
    vector_SDL_print_car(map, sdl, *((struct point *)steps->tail->data));

    next = vector_SDL_mouse_choice(map);
    
    if(next.x == -1 || next.y == -1)
    {
      continuer = 0;
    }
    if( next.x >= A.x && next.x <= B.x && next.y >= A.y && next.y <= B.y )
    {
      struct point * st = (struct point *)malloc(sizeof(struct point));
      st->x = next.x;
      st->y = next.y;
      list_add(steps, st);
      n = n+1;
    
      if(map->grid[next.x][next.y] == '#')
	{
	  printf("You loose the game!\n");
	  continuer = 0;
	}
      else if((map->grid[next.x][next.y])-1 == checkpoint)
	{
	  printf("+1\n");
	  checkpoint++;
	  printf("%c\n",checkpoint);
	  printf("%d\n", maxcheckpoint);
	  if (checkpoint == (maxcheckpoint + '0'))
	    {  printf("presque!\n");
	      cheater = 0;}
	}
      else if((map->grid[next.x][next.y])+1 == checkpoint)
	{
	  printf("-1\n");
	  checkpoint--;
	  printf("%c\n",checkpoint);
	  
	}
      else if((map->grid[next.x][next.y] == '*') && (!cheater))
	{
	  printf("You win!\nCongratulation!\n");
	  printf("You did it in %d steps.\n",n);
	  continuer = 0;
	}
      else if((map->grid[next.x][next.y]) <= checkpoint-2)
	{
	  if(cheater)
	    {
	      printf("You are cheating!\nLooser!\n");
	      continuer = 0;
	    }
	  else
	    {
	      printf("You win!\nCongratulation!\n");
	      continuer = 0;
	    }
	}
      else if((map->grid[next.x][next.y]) >= checkpoint+2)
	{
	  printf("You missed a checkpoint.\n");
	  continuer = 0;
	  }
	  else{}
    
      if(next.x == A.x)
	{
	  vitx--;
	}
      if(next.x == B.x)
	{
	  vitx++;
	}
      if(next.y == A.y)
	{
	  vity--;
	}
      if(next.y == B.y)
	{
	  vity++;
	}
    }
      
  }
  vector_SDL_free(sdl);
  list_free(steps);
  free(start);
  return 1;
}


int solve_and_print(char * filename, struct map * map)
{
  struct list * solution = solve(filename);
  void* sdl = vector_SDL_init(map);
  struct point previous;
  struct point current;
  struct lelement * lelement = solution->tail;
  current.x = ((struct point *)lelement->data)->x;
  current.y = ((struct point *)lelement->data)->y;
  char resume = 1;
  
  vector_SDL_print(map, sdl);
  

  while(lelement != NULL)
    {
      SDL_Delay(50);
      previous.x = current.x;
      previous.y = current.y;
      
      current.x = ((struct point *)lelement->data)->x;
      current.y = ((struct point *)lelement->data)->y;
      
      vector_SDL_print_car(map, sdl, current);
      vector_SDL_print_line(map, sdl, previous, current);
      lelement = lelement->prev;
    }
  


  vector_SDL_Wait();

  list_free(solution);
  vector_SDL_free(sdl);
  return 1;
}
