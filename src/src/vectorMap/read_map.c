#include <vectorMap/read_map.h>
#include <vectorErrno/vector_errno.h>

struct map * vector_map_load(char *filename)
{
  errno = 0;
  FILE* file = fopen(filename, "r");
  if (file == NULL)
    {
      goto fopenError;
    }

  struct map *p_map = NULL;
  if ((p_map = get_map_size(file)) == NULL)
    {
      goto getMapSizeError;
    }

  if ((p_map->grid = malloc(p_map->w*sizeof(p_map->grid))) == NULL)
    {
      goto mallocMapError;
    }

  char * p_grid;
  if ((p_grid = malloc(p_map->h * p_map->w * sizeof(p_map->grid))) == NULL)
    {
      goto mallocGridError;
    }

  for (int i = 0 ; i < p_map->w; i++)
    {
      p_map->grid[i] = &(p_grid[i*p_map->h]);
    }

  enum err err;
  if (err = map_parse(file, p_map))
    {
      goto mapParsingError;
    }

  return p_map;

 mapParsingError:
  switch (err)
    {
    case SIZE:
      fprintf(stderr, "Wrong file format (wrong size ?).\n");
      break;
    case UNKNOWN_CHAR:
      fprintf(stderr, "Wrong character encountered.\n");
      break;
    }

 mallocGridError:
  free(p_grid);

 mallocMapError:
  free(p_map->grid);
  free(p_map);

 getMapSizeError:
  fclose(file);

 fopenError:
  if (errno)
    {
      perror(NULL);
    }
  return NULL;
}

struct map * get_map_size(FILE* file)
{
  while(fgetc(file) == '-')
    {
      while(fgetc(file) != '\n' && fgetc(file) != EOF);
    }

  fseek(file, -1, SEEK_CUR);

  errno = 0;
  struct map *p_map = malloc(sizeof(struct map));
  if (p_map == NULL)
    {
      return NULL;
    }

  if (fscanf(file, "%d %d\n", &(p_map->h), &(p_map->w)) != 2)
    {
      return NULL;
    }

  return p_map;
}

enum err map_parse(FILE* file, struct map * p_map)
{
  char c;
  int i = 0, j = 0;
  p_map->maxcheckpoint = 0;
  while((c = fgetc(file)) != EOF)
    {
      switch (c)
	{
	case '\n':
	  j++;
	  i = 0;
	  break;
	case '-':
	  while(fgetc(file) != '\n' && fgetc(file) != EOF);
	  break;
	default:
	  if (c == '#' || isdigit(c) || c == '*')
	    {
	      if (i >= p_map->w || j >= p_map->h)
		{
		  return SIZE;
		}
	      if ( c == '*' )
		{
		  p_map->D.x = i;
		  p_map->D.y = p_map->h-j-1;
		}
	      if ((isdigit(c))&&((atoi(&c)>(p_map->maxcheckpoint))))
		{ 
		  p_map->maxcheckpoint = atoi(&c);
		}
		p_map->grid[i][p_map->h-j-1] = c;
		i++;
		}
	      else
		{
		  return UNKNOWN_CHAR;
		}
	      break;
	    }
	}
      return 0;
    }

  void vector_map_free(struct map * p_map)
  {
    free(p_map->grid);
    free(p_map);
  }

  void vector_map_print(struct map * p_map)
  {
    for (int j = 0; j < p_map->h; j++)
      {
	for (int i = 0; i < p_map->w; i++)
	  {
	    printf("%c", p_map->grid[i][p_map->h - j - 1]);
	  }
	printf("\n");
      }
  }
