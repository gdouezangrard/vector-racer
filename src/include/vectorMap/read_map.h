#ifndef MAP_UTILS_H_INCLUDED
#define MAP_UTILS_H_INCLUDED
#define color(param) printf("\033[%sm",param)
#define LOGLEVEL 1

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

struct point
{
  int x;
  int y;
};

struct map
{
  int h;
  int w;
  char** grid;
  struct point D;
  int maxcheckpoint;
};

enum err
{
  UNKNOWN_CHAR = 1, SIZE
};

struct map * vector_map_load(char *);
struct map * get_map_size(FILE *);
enum err map_parse(FILE *, struct map *);
void vector_map_free(struct map *);
void vector_map_print(struct map * p_map);

#endif
