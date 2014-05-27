#include <stdio.h>
#include "vectorErrno/vector_errno.h"

int errno;
const char *err_code[] = {"ALRIGHT","ERROR_OPENING_FILE","ERROR_PARSING_FILE","ERROR_ALLOCATING_MEMORY"};

void errno_print_errno(int errno)
{
  printf("%s \n",err_code[errno]);
}

void set_errno (int c)
{
  errno = c;
}
