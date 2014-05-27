#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <vectorMap/read_map.h>
#include <vectorDll/vector_dll.h>
#include <vectorSolver/solver.h>
#include <vectorSDL/vector_sdl.h>

int game(struct map * map);

int solve_and_print(char * filename, struct map * map);

#endif
