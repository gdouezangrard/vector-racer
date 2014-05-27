#include <vectorMap/read_map.h>
#include <vectorSDL/vector_sdl.h>

#define BOX 16
#define CAR (BOX/2)
#define LINE BOX/8
#define CHOICE (BOX*3)/4

struct point* reverse(struct map* map, struct point* P)
{
  P->y = map->h - P->y - 1;
}

struct sdl* vector_SDL_init(struct map* map)
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Surface *screen = NULL;
  screen = SDL_SetVideoMode(BOX*map->w, BOX*map->h, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Vector Race", NULL);
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

  SDL_Surface *wall = NULL;
  wall = SDL_CreateRGBSurface(SDL_HWSURFACE, BOX-1 , BOX-1 , 32, 0, 0, 0, 0);
  SDL_FillRect(wall, NULL, SDL_MapRGB(wall->format, 2, 95, 22));

  SDL_Surface *start = NULL;
  start = SDL_CreateRGBSurface(SDL_HWSURFACE, BOX-1 , BOX-1 , 32, 0, 0, 0, 0);
  SDL_FillRect(start, NULL, SDL_MapRGB(start->format, 255, 125, 0));

  
  SDL_Surface *roadimpair = NULL;
  roadimpair = SDL_CreateRGBSurface(SDL_HWSURFACE, BOX-1 , BOX-1 , 32, 0, 0, 0, 0);
  SDL_FillRect(roadimpair, NULL, SDL_MapRGB(roadimpair->format, 67, 67, 67));
  

  SDL_Surface *road = NULL;
  road = SDL_CreateRGBSurface(SDL_HWSURFACE, BOX-1 , BOX-1 , 32, 0, 0, 0, 0);
  SDL_FillRect(road, NULL, SDL_MapRGB(road->format, 125, 125, 125));

  SDL_Surface *car = NULL;
  car = SDL_CreateRGBSurface(SDL_HWSURFACE, CAR , CAR , 32, 0, 0, 0, 0);
  SDL_FillRect(car, NULL, SDL_MapRGB(car->format, 255, 0, 0));


  SDL_Surface *line = NULL;
  line = SDL_CreateRGBSurface(SDL_HWSURFACE, LINE , LINE , 32, 0, 0, 0, 0);
  SDL_FillRect(line, NULL, SDL_MapRGB(line->format, 255, 0, 0));

  SDL_Surface *choice = NULL;
  choice = SDL_CreateRGBSurface(SDL_HWSURFACE, CHOICE, CHOICE, 32, 0, 0, 0, 0);
  SDL_FillRect(choice, NULL, SDL_MapRGB(choice->format, 0, 255, 0));

  struct sdl* sdl = malloc(sizeof(struct sdl));
  sdl->screen = screen;
  sdl->start = start;
  sdl->wall = wall;
  sdl->road = road;
  sdl->roadimpair = roadimpair;
  sdl->car = car;
  sdl->line = line;
  sdl->choice = choice;

  return sdl;
}

int vector_SDL_print(struct map* map, struct sdl* sdl)
{
  SDL_Rect position = {0, 0, 0, 0};
  int i = 0;
  int j = 0;
  SDL_FillRect(sdl->screen, NULL, SDL_MapRGB(sdl->screen->format, 255, 255, 255));
  for (i = 0; i < map->h; i++)
  {
    position.x = BOX*j+1;
    position.y = BOX*(map->h -(i+1));
    for (j = 0; j < map->w; j++)
    {
      position.x = BOX*j+1;
      position.y = BOX*(map->h -(i+1));
      if (map->grid[j][i] == '#')
	{
	  SDL_BlitSurface(sdl->wall, NULL, sdl->screen, &position);
	}
      else if (map->grid[j][i] == '*')
	{
	  SDL_BlitSurface(sdl->start, NULL, sdl->screen, &position);
	}
      else
	{
	  if((map->grid[j][i]) % 2)
	    SDL_BlitSurface(sdl->road, NULL, sdl->screen, &position);
	  else
	    SDL_BlitSurface(sdl->roadimpair, NULL, sdl->screen, &position);
	}
    }
    j = 0;
  }
  
  /*//test
  struct point A,B,P;
  A.x = 1;
  A.y = 7;
  B.x = 5;
  B.y = 3;
  P.x = 0;
  P.y = 10;
  vector_SDL_print_car(map, sdl, P);
  vector_SDL_print_car(map, sdl, A);
  vector_SDL_print_car(map, sdl, B);
  vector_SDL_print_line(map, sdl, A, B);
  vector_SDL_print_choice(map, sdl, A, B);
  *///test

  SDL_Flip(sdl->screen);

  return 0;

}

int vector_SDL_free(struct sdl* sdl)
{
  SDL_FreeSurface(sdl->start);
  SDL_FreeSurface(sdl->wall);
  SDL_FreeSurface(sdl->screen);
  SDL_FreeSurface(sdl->road);
  SDL_FreeSurface(sdl->roadimpair);
  SDL_FreeSurface(sdl->car);
  SDL_FreeSurface(sdl->line);
  SDL_FreeSurface(sdl->choice);

  free(sdl);

  SDL_Quit();

  return 0;
}

int vector_SDL_print_car(struct map* map, struct sdl * sdl, struct point P)
{
  reverse(map, &P);
  int xp,yp;
  xp = (P.x*BOX) + BOX/2;
  yp = (P.y*BOX) + BOX/2;
  SDL_Rect position = {0, 0, 0, 0};
  position.x = xp - CAR/2;
  position.y = yp - CAR/2;
  SDL_BlitSurface(sdl->car, NULL, sdl->screen, &position);
  SDL_Flip(sdl->screen);
  return 0;
}

int vector_SDL_print_line(struct map* map, struct sdl* sdl, struct point A, struct point B)
{
  reverse(map, &A);
  reverse(map, &B);
  //Bresenham's algorithm
  int xa,xb,ya,yb;
  xa = A.x*BOX + BOX/2;
  xb = B.x*BOX + BOX/2;
  ya = A.y*BOX + BOX/2;
  yb = B.y*BOX + BOX/2;
  int dx,dy;
  SDL_Rect position = {0, 0, 0, 0};
  dy = yb - ya;
  dx = xb - xa;

  if(dx)
  {
    if(dx>0)
    {
      if(dy)
      {
        if(dy>0) // first quadran
        {
          if(dx>=dy)
          {
            int e = dx;
            dx = e*2;
            dy = dy*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              xa++;
              if(xa == xb)
              {
                continuer = 0;
              }
              e = e - dy;
              if(e<0)
              {
                ya++;
                e = e + dx;
              }

            }
          }//if5
          else
          {
            int e = dy;
            dy = e*2;
            dx = dx*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              ya++;
              if(ya == yb)
              {
                continuer = 0;
              }
              e = e - dx;
              if(e<0)
              {
                xa++;
                e = e + dy;
              }

            }
          }//else5
        }//if4
        else // fourth quadran
        {
          if(dx>=-dy)
          {
            int e = dx;
            dx = e*2;
            dy = dy*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              xa++;
              if(xa == xb)
              {
                continuer = 0;
              }
              e = e + dy;
              if(e<0)
              {
                ya--;
                e = e + dx;
              }
            }
          }//if5
          else
          {
            int e = dy;
            dy = e*2;
            dx = dx*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              ya--;
              if(ya == yb)
              {
                continuer = 0;
              }
              e = e + dx;
              if(e>0)
              {
                xa++;
                e = e + dy;
              }
            }
          }//else5
        }//else4
      }//if3
      else // dy = 0 (and dx > 0)
      {
        while(xa < xb)
        {
          position.x = xa - LINE/2;
          position.y = ya - LINE/2;
          SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
          xa++;
        }
      }//else3
    }//if2
    else
    {
      if(dy)
      {
        if(dy > 0) // 2nd quadran
        {
          if(-dx >= dy)
          {
            int e = dx;
            dx = e*2;
            dy = dy*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              xa--;
              if(xa == xb)
              {
                continuer = 0;
              }
              e = e + dy;
              if(e>=0)
              {
                ya++;
                e = e + dx;
              }
            }
          }//if5
          else
          {
            int e = dy;
            dy = e*2;
            dx = dx*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              ya++;
              if(ya == yb)
              {
                continuer = 0;
              }
              e = e + dx;
              if(e<=0)
              {
                xa--;
                e = e + dy;
              }
            }
          }//else5
        }//if4
        else //third quadran dy < 0 (and dx < 0)
        {
          if(dx<=dy)
          {
            int e = dx;
            dx = e*2;
            dy = dy*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              xa--;
              if(xa == xb)
              {
                continuer = 0;
              }
              e = e - dy;
              if(e>=0)
              {
                ya--;
                e = e + dx;
              }
            }
          }//if5
          else
          {
            int e = dy;
            dy = e*2;
            dx = dx*2;
            char continuer = 1;
            while(continuer)
            {
              position.x = xa - LINE/2;
              position.y = ya - LINE/2;
              SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
              ya--;
              if(ya == yb)
              {
                continuer = 0;
              }
              e = e - dx;
              if(e>=0)
              {
                xa--;
                e = e + dy;
              }
            }
          }//else5
        }//else4
      }//if3
      else //dy = 0 (and dx < 0)
      {
        while(xa > xb)
        {
          position.x = xa - LINE/2;
          position.y = ya - LINE/2;
          SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
          xa--;
        }
      }//else3
    }//else2
  }//if1
  else //dx = 0
  {
    if(dy)
    {
      if(dy>0)
      {
        while(ya < yb)
        {
          position.x = xa - LINE/2;
          position.y = ya - LINE/2;
          SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
          ya++;
        }
      }//if3
      else
      {
        while(ya > yb)
        {
          position.x = xa - LINE/2;
          position.y = ya - LINE/2;
          SDL_BlitSurface(sdl->line, NULL, sdl->screen, &position);
          ya--;
        }
      }//else3
    }//if2
    else
    {
      // dx = dy = 0
    }
  }//else1
  SDL_Flip(sdl->screen);
  return 0;
}

int vector_SDL_print_choice(struct map* map, struct sdl* sdl, struct point A, struct point B)
{
  reverse(map, &A);
  reverse(map, &B);
  SDL_Rect position = {0, 0, 0, 0};

  for(int i = A.x; i <= B.x; i++)
  {
    for(int j = B.y; j <= A.y; j++)
    {
      position.x = i*BOX + (BOX/2 - CHOICE/2);
      position.y = j*BOX + (BOX/2 - CHOICE/2);
      SDL_BlitSurface(sdl->choice, NULL, sdl->screen, &position);
    }
  }
  SDL_Flip(sdl->screen);
  return 0;
}

struct point vector_SDL_mouse_choice(struct map* map)
{
  struct point current = {-1, -1};//Initiate to (-1, -1) to make difference between case selection and exiting the game.

  SDL_Event event;
  int continuer = 1;
  while(continuer)
  {
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
      continuer = 0;
      return current;
      break;
      case SDL_MOUSEBUTTONUP:
      if (event.button.button == SDL_BUTTON_LEFT)
      {
        continuer = 0;
        current.x = (event.button.x)/BOX;
        current.y = (event.button.y)/BOX;
        reverse(map, &current);
        return current;
      }
      break;
      default:
      break;
    }
  }
}

void vector_SDL_Wait()
{
  SDL_Event event;
  char resume = 1;
  while(resume)
    {
      SDL_WaitEvent(&event);
      switch(event.type)
	{
	case SDL_QUIT:
	  resume = 0;
	  break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
            {
	    case SDLK_ESCAPE:
	      resume = 0;
	      break;
	    default:
	      break;
            }
	default:
	  break;
	}
    }
}
