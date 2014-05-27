#include <vectorSteps/read_steps.h>
#include <vectorMap/read_map.h>

enum ERROR steps_get_accel(FILE *file, char * file_name, struct steps *steps);
enum ERROR steps_get_start(FILE *file, char * file_name, struct steps *steps);
enum ERROR steps_get_steps(FILE *file, char * file_name, struct steps *steps);
enum ERROR steps_get_accel_allowed(FILE *file, char *file_name,  struct steps *steps);
enum ERROR steps_movements(FILE *file, char *file_name, struct steps *steps);
enum ERROR steps_parse(char *f, struct steps *steps);
void print_error(enum ERROR error);

enum ERROR steps_get_accel(FILE *file, char * file_name, struct steps *steps)
{
  char str[LEN];
  char c;
  enum ERROR error = noer;
  fgets(str,LEN,file);
  steps->num_accel = 0;
  if(strcmp(str,"Accel : ") != 0)
  {
    error = er1;
  }
  c = fgetc(file);
  if(isdigit(c))
  {
    do
    {
      steps->num_accel = (steps->num_accel)*10 + c-'0';
      c = fgetc(file);
    }
    while(isdigit(c));
      if((c == '\n' || c == EOF) && steps->num_accel != 0)
      {
        error = noer;
      }
      else
      {
        error = er1;
      }
  }
  else
  {
    error = er1;
  }
  return error;
}

enum ERROR steps_get_start(FILE *file, char * file_name, struct steps *steps)
{
  char str[LEN];
  enum ERROR error = noer;
  fgets(str,LEN,file);
  if(strcmp(str,"Start : ") != 0)
  {
    error = er5;
    return error;
  }
  if(fgetc(file) != '\n')
  {
    steps->starting_position = (struct vector *)malloc(sizeof(struct vector));
    fseek(file,-1,SEEK_CUR);
    if((fscanf(file,"%d",&steps->starting_position->x) == 1) && (fgetc(file) == ',') && (fscanf(file,"%d",&steps->starting_position->y) == 1) && (fgetc(file) == '\n'))
    {
      error = noer;
      return error;
    }
    else
    {
      error = er6;
      free(steps->accel_allowed);
      free(steps->starting_position);
      return error;
    }
  }
  else
  {
    error = er6;
    return error;
  }
}

enum ERROR steps_get_steps(FILE *file, char * file_name, struct steps *steps)
{
  char str[LEN];
  char c;
  enum ERROR error = noer;
  fgets(str,LEN,file);
  steps->num_steps = 0;
  if(strcmp(str,"Steps : ") != 0)
  {
    error = er2;
    return error;
  }
  c = fgetc(file);
  if(isdigit(c))
  {
    do
    {
      steps->num_steps = steps->num_steps*10 + c-'0';
      c = fgetc(file);
    }
    while(isdigit(c));
    if((c == '\n' || c == EOF) && steps->num_steps != 0)
    {
      error = noer;
      return error;
    }
    else
    {
      error = er2;
      free(steps->accel_allowed);
      free(steps->starting_position);
      return error;
    }
  }
  else
  {
    error = er2;
    return error;
  }
}

enum ERROR steps_get_accel_allowed(FILE *file, char *file_name, struct steps *steps)
{
  int cmp = 0;
  char c = fgetc(file);
  enum ERROR error = noer;
  int *tmp = NULL;
  steps->accel_allowed = (struct vector *)malloc(steps->num_accel*sizeof(struct vector));
  int i = 0;
  while(c != 'S' && c != EOF && cmp < steps->num_accel)
  {
    fseek(file,-1,SEEK_CUR);
    if((fscanf(file,"%d", &steps->accel_allowed[i].x) == 1) && (fgetc(file) == ',') && (fscanf(file,"%d",&steps->accel_allowed[i].y) == 1) && (fgetc(file) == '\n'))
    {
      c = fgetc(file);
      cmp ++;
      i++;
    }
    else
    {
      error = er3;
      free(steps->accel_allowed);
      return error;
    }

  }
  if(cmp == steps->num_accel)
  {
    if(c == 'S' && fgetc(file) == 't' && fgetc(file) == 'a')
    {
      fseek(file, -3, SEEK_CUR);
      error = noer;
      return error;
    }
    else
    {
      error = er6;
      return error;
    }
  }
  else
  {
    error = er4;
    free(steps->accel_allowed);
    return error;
  }
}

enum ERROR steps_get_movements(FILE *file, char *file_name, struct steps *steps)
{
  int cmp = 0;
  char c = fgetc(file);
  enum ERROR error = noer;
  int *tmp = NULL;
  steps->movements = (struct vector *)malloc(steps->num_steps*sizeof(struct vector));
  int i = 0;
  while(c != EOF && cmp < steps->num_steps)
  {
    fseek(file,-1,SEEK_CUR);
    if((fscanf(file,"%d",&steps->movements[i].x) == 1) && (fgetc(file) == ',') && (fscanf(file,"%d",&steps->movements[i].y) == 1) && (fgetc(file) == '\n'))
    {
      c = fgetc(file);
      cmp ++;
      i++;
    }
    else
    {
      error = er3;
      free(steps->accel_allowed);
      free(steps->starting_position);
      free(steps->movements);
      return error;
    }
  }
  if(c == EOF && cmp == steps->num_steps)
  {
    fseek(file,-1,SEEK_CUR);
    error = noer;
    return error;
  }
  else
  {
    error = er5;
    free(steps->accel_allowed);
    free(steps->starting_position);
    free(steps->movements);
    return error;
  }
}

/* void print_error(enum ERROR error) */
/* { */
/*   switch(error){ */
/*   case er1: */
/*     printf("Invalid accel definition. Definition must take this format: Accel : number\n"); */
/*     break; */
/*   case er2: */
/*     printf("Invalid steps definition. Definition must take this format: Steps : number.\n"); */
/*     break; */
/*   case er3: */
/*     printf("Invalid vector definition. Definitions must take this format: number,number\n"); */
/*     break; */
/*   case er4: */
/*     printf("Number of vectors must be equal to number of accelerations\n"); */
/*     break; */
/*   case er5: */
/*     printf("Number of vectors must be equal to number of steps\n"); */
/*     break; */
/*   case er6: */
/*     printf("Invalid start definition. Definition must take this format: Start : number,number.\n"); */
/*     break; */
/*   case er7: */
/*     printf("Enter correct file name example.txt!\n"); */
/*     break; */
/*   case noer: */
/*     printf("Correct file \n"); */
/*     break; */
/*   } */
/* } */

void steps_free(struct steps *steps)
{
  free(steps->starting_position);
  free(steps->accel_allowed);
  free(steps->movements);
  free(steps);
}

struct steps *steps_empty()
{
  struct steps *steps = (struct steps *)malloc(sizeof(struct steps));
  steps->starting_position = NULL;
  steps->accel_allowed = NULL;
  steps->movements = NULL;
  return steps;
}

enum ERROR steps_parse(char *f, struct steps *steps)
{
  enum ERROR error = noer;
  FILE *file = fopen(f,"r");
  if(file != NULL)
  {
    if((error = steps_get_accel(file,f,steps)) == noer)
    {
      if((error = steps_get_accel_allowed(file,f,steps)) == noer)
      {
        if((error = steps_get_start(file,f,steps)) == noer)
        {
          if((error = steps_get_steps(file,f,steps)) == noer)
          {
            if((error = steps_get_movements(file,f,steps)) == noer);
          }
        }
      }
    }
    return error;
  }
  error = er7;
  return error;
}

struct steps * steps_load(char *f)
{
  struct steps * steps = steps_empty();
  if(steps_parse(f,steps) == noer)
  {
    return steps;
  }
  free(steps);
  return NULL;
}

void steps_print(struct steps *steps)
{
  printf("Accel : %d\n",steps->num_accel);
  for(int i = 0;i<steps->num_accel; i++)
  {
    printf("%d,%d\n",steps->accel_allowed[i].x,steps->accel_allowed[i].y);
  }
  printf("Start : %d,%d\n",steps->starting_position->x,steps->starting_position->y);
  printf("Steps : %d\n",steps->num_steps);
  for(int i = 0;i<steps->num_steps; i++)
  {
    printf("%d,%d\n",steps->movements[i].x,steps->movements[i].y);
  }
}

int steps_verify(struct steps *steps)
{
  struct vector current_speed = {0,0};
  struct vector current_difference = {0,0};
  int i = 0, j = 0, bool = 1;
  while((i<steps->num_steps) && (bool == 1))
  {
    bool = 0;
    j = 0;
    current_difference.x = steps->movements[i].x - current_speed.x;
    current_difference.y = steps->movements[i].y - current_speed.y;
    while((j<steps->num_accel) && (bool == 0))
    {
      if((current_difference.x == steps->accel_allowed[j].x) && (current_difference.y == steps->accel_allowed[j].y))
      {
        bool = 1;
      }
      j++;
    }

    current_speed.x = steps->movements[i].x;
    current_speed.y = steps->movements[i].y;
    i++;
  }
  if(bool == 0)
  {
    return 0;
  }
  return 1;
}

//TODO//

/* int steps_is_solution(char *fs, char *fm) */
/* { */
/*   struct steps *steps = steps_load(fs); */
/*   struct map *map = vector_map_load(fm); */
/*   if(steps != NULL && map != NULL) */
/*     { */
/*       char visited_numbers[VISITED]; */
/*       char c; */
/*       if(steps_verify(steps)) */
/* 	{ */
/* 	  c = map->grid[starting_position->x][steps->starting_position->y]; */
/* 	  if(c  == '*') */
/* 	    { */
/* 	      visited_numbers[i] */
/* 		int j = 0; */
/* 	      int i = 0 */
/* 		struct vector current_position = {steps->movements[0].x, steps->movements[0].y}; */
/* 	      while(j<steps->num_steps-1) */
/* 		{ */
/* 		  c = map->grid[current_position.x][current_position.y]; */
/* 		  if(isdigit(c) == 0) */
/* 		    return 0; */
/* 		  j++; */
/* 		  current_position.x = current_position.x + steps->movements[j].x; */
/* 		  current_position.y = current_position.y + steps->movements[j].y; */
/* 		} */
/* 	      if((c = map->grid[steps->movements[j].x][steps->movements[j].y]) == '*' || (c == '1')) */
/* 		return 1; */
/* 	    } */
/* 	} */
/*     } */
/*   return 0; */
/* } */
