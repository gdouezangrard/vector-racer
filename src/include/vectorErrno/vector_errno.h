#ifndef VECTOR_ERRNO_H_INCLUDED
#define VECTOR_ERRNO_H_INCLUDED

#define ALRIGHT                      0
#define ERROR_OPENING_FILE           1
#define ERROR_PARSING_FILE           2
#define ALLOCATION_ERROR             3

extern int errno;

void errno_print_errno(int errno);
void set_errno (int c);

#endif
