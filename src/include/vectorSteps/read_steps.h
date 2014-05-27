#ifndef READ_FILE_H
#define READ_FILE_H
#define LEN 9
#define VISITED 12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

struct vector
{
  int x;
  int y;
};

struct steps
{
  int num_accel;
  int num_steps;
  struct vector *starting_position;
  struct vector *accel_allowed;
  struct vector *movements;
};

//ERRORS
enum ERROR {er1,er2,er3,er4,er5,er6,er7,noer};
struct steps *steps_empty();

//main reading function
struct steps *steps_load(char *);
enum ERROR steps_parse(char *, struct steps *);

//function to free steps structure
void steps_free(struct steps *);
void steps_print(struct steps *);
int steps_verify(struct steps *);
int steps_is_solution(char *, char *);

#endif
