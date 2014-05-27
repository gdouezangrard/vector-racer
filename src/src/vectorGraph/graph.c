#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "graph.h"
#include "link.h"

#define MAXVERTEX 2000
#define EMPTY_LIST NULL


/***** Structure definition ******/

struct link;

struct lelement
{
  void *data;
  struct lelement *next;
};


struct vertex
{
  int vertexID;
  char *tag;
};

struct graph
{
  struct link **neighbors; //Adjacency list
  vertex* vertex[MAXVERTEX];
  int number_edges;
  int number_vertices;
};
/******************** Graph Functions **********************/

struct graph* graph_empty()
{
	struct graph *g = malloc(sizeof(struct graph));
	g->neighbors[0]= NULL;
	g->number_vertices = 0;
	g->number_edges = 0;
	return g;
}

//Design note: the vertex is appended to the array of vertexs: vertexID = nbVertices-1
struct vertex* graph_add_vertex(graph* g)
{
	assert(g != NULL);
	assert(g->number_vertices < MAXVERTEX);
	//Initialize the new vertex (adjacency,id and tag)
	//	g->neighbors[g->number_vertices] = EMPTY_LIST;
	g->vertex[g->number_vertices] = malloc(sizeof(vertex));
	g->vertex[g->number_vertices]->vertexID = g->number_vertices;
	g->vertex[g->number_vertices]->tag = NULL;
	g->number_vertices++;
	//return the new vertex
	return g->vertex[g->number_vertices-1];
}

int vertex_get_id(const vertex* v)
{
	return v->vertexID;
}

vertex* graph_get_vertex_from_id(const graph* g, int id)
{
	return g->vertex[id];
}

int graph_add_edge(graph* g, vertex* v1, vertex* v2)
{
	assert(g != NULL);
	assert(v1 != NULL);
	assert(v2 != NULL);

	struct lelement *n1 = malloc(sizeof(struct lelement));
	n1->data = v1;

	struct lelement *n2 = malloc(sizeof(struct lelement));
	n2->data = v2;
	
	//Adds v2 to the neighbor list of v1 and v2 to the one of v1
	lnk__add_tail(g->neighbors[v1->vertexID -1],n2); 
	lnk__add_tail(g->neighbors[v2->vertexID -1],n1);
	g->number_edges++;

	return EXIT_SUCCESS;
}

int graph_remove_edge(graph* g, vertex* v1, vertex* v2)
{
	//Adds v2 to the neighbor list of v1 and v2 to the one of v1

  free(lnk__remove_tail(g->neighbors[v1->vertexID]));
  free(lnk__remove_tail(g->neighbors[v1->vertexID]));
  return 0;
}


int graph_is_vert_in(const graph* g, const vertex* v)
{
	assert(g != NULL);
	assert(v != NULL);
	if(v->vertexID < g->number_vertices)
	{
		return v == g->vertex[v->vertexID];
	}
	else
		return EXIT_SUCCESS;
}


int graph_is_edge_in(const graph* g, const vertex* v1, const vertex* v2)
{
	assert(v1 != NULL);
	assert(v2 != NULL);
	assert(g != NULL);

	return (lnk__find(g->neighbors[v1->vertexID],v2->vertexID));
}

int graph_number_vertex(const graph* g)
{
	return g->number_vertices;
}

int graph_number_edges(const  graph* g)
{
	return g->number_edges;
}

char *graph_get_vertex_tag(const graph* g, const vertex* v)
{
	assert(g != NULL);
	assert(v != NULL);
	return v->tag;
}

int graph_set_vertex_tag(struct graph* g,struct vertex* v, char *tag)
{
	assert(g != NULL);
	assert(v != NULL);
	v->tag = tag;
	return EXIT_SUCCESS;
}

void graph_free(struct graph* g)
{
	assert(g != NULL);
	int i;
	//Free every vertex and every adjacency list
	for(i = 0; i < g->number_vertices; i++)
	{
		free(g->vertex[i]);
		lnk__free(g->neighbors[i]);
	}
	free(g);
}


