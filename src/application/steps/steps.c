#include "vectorSteps/read_steps.h"

int main(int argc, char ** argv) {
	if (argc == 2) {
		struct steps * steps = steps_load(argv[1]);
		if(steps != NULL)
		{
			steps_print(steps);
		}
	}
	return 0;
}
