all : graph.o link.o test.o
	gcc -Wall -Wextra -ggdb graph.o link.o test.o -o graph

link.o : link.c link.h
	gcc -c -ggdb link.c

graph.o : graph.c graph.h
	gcc -c -ggdb  graph.c 

test.o : test.c
	gcc -c -ggdb test.c


clean : 
	rm *.o *~