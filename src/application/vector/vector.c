#include <stdio.h>
#include <stdlib.h>
#include <vectorMap/read_map.h>
#include <vectorDll/vector_dll.h>
#include <vectorSDL/vector_sdl.h>

int main(int argc, char ** argv)
{
  if (argc == 2)
  {
    struct map * map = vector_map_load(argv[1]);

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
      }
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
    vector_SDL_free(sdl);
    list_free(steps);
    free(start);
    vector_map_print(map);
    vector_map_free(map);
  }

  else
  {
    printf("Usage: ./vector 'map_file.txt'\n");
  }
  return 0;
}
