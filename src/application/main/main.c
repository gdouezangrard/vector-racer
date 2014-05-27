#include <stdio.h>
#include <stdlib.h>
#include <vectorGame/vectorgame.h>

int main(int argc , char **argv)
{
  if (argc == 2)
    {
      struct map * map = vector_map_load(argv[1]);
      vector_map_print(map);
      int choice = 0;
      char resume = 1;
      while (resume)
	{
	  printf("What do you want to do?\n");
	  printf("Play (1) Solve (2) Quit (3)\n");
	  if (scanf("%d", &choice) == 1)
	    {
	      switch(choice)
		{
		case 1:
		  printf("Jouons!\n");
		  resume = game(map);
		  break;
		case 2:
		  resume = solve_and_print(argv[1],map);
		  break;
		case 3:
		  resume = 0;
		  break;
		default:
		  break;
		}
	    }
	  int c = 0;
	  while (c != '\n' && c != EOF)
	    {
	      c = getchar();
	    }
	}
    }
  else
    {
      printf("Usage: ./vector 'map_file.txt'\n");
    }
  
  return 0;
}
