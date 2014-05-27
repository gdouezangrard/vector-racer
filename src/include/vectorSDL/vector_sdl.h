#ifndef VECTOR_SDL
#define VECTOR_SDL

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

struct sdl
{
  SDL_Surface * screen;
  SDL_Surface * wall;
  SDL_Surface * start;
  SDL_Surface * roadimpair;
  SDL_Surface * road;
  SDL_Surface * car;
  SDL_Surface * line;
  SDL_Surface * choice;
};

struct sdl* vector_SDL_init(struct map*);

int vector_SDL_print(struct map*,struct sdl*);
/*Print the map.
  Return 0 for success.*/

int vector_SDL_free(struct sdl*);
/*Return 0 in case of success.*/

int vector_SDL_print_car(struct map*, struct sdl*, struct point);
/*Print current car position.
  Return 0 in case of success.*/

int vector_SDL_print_line(struct map*, struct sdl*, struct point A, struct point B);
/*Print a line between previous car's position A and current car's position B.
  Return 0 in case of success.*/

int vector_SDL_print_choice(struct map* map, struct sdl* sdl, struct point A, struct point B);
/*Print possible future car's position.
  Return 0 in case of success.*/

struct point vector_SDL_mouse_choice(struct map*);
/*Return a structure point choosed by the user with the mouse.
 If the function return the point (-1, -1), the user choosed to close the game by clicking on the button Quit.*/

void vector_SDL_Wait();
/*Wait until someone click on the cross
  Be careful! Do not call this function if there is no SDL's window.*/
#endif
