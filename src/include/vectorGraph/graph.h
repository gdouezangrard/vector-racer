#ifndef _STRUCTGRAPH_
#define _STRUCTGRAPH_


/************ Structure definition ***************/

typedef struct vertex vertex;
typedef struct graph graph;
typedef void* vertex_tag;
//!\typedef Function to be used into graph_connex_dfs
typedef int (*vertex_action)(graph* g, vertex* v, void* data);


/********************* Function declarations **********************/

//!\brief Creates an empty graph
graph*    graph_empty();
//!\brief Add a vertex to the graph and returns it
//!\return The new graph vertex
vertex*   graph_add_vertex(graph* g);
//!\brief Gets the id of the vertex. All the vertices have a unique id in [0,nb_vertices[
int       vertex_get_id(const vertex* v);
//!\brief Gets the vertex of id 'id'. All the vertices have a unique id in [0,nb_vertices[
vertex*   graph_get_vertex_from_id(const graph* g, int id);
//!\brief Add an edge between v1 and v2
int 	    graph_add_edge(graph* g, vertex* v1, vertex* v2);
//!\brief Remove the edge between v1 and v2. If it doesn't exist, the graph in unchanged, if there is multiple edges between v1 and v2, only one is removed.
int       graph_remove_edge(graph* g, vertex* v1, vertex* v2);
//!\brief Says if v is part of the graph or belongs to an other graph.
//!\note for all the other functions, vertice must belong to the graph in parameter
int       graph_is_vert_in(const graph* g, const vertex* v);
//!\brief Says if there is an edge between v1 and v2 in the graph
int       graph_is_edge_in(const graph* g, const vertex* v1, const vertex* v2);
//!\brief Returns the size of the graph (vertices)
int       graph_number_vertex(const graph* g);
//!\brief Returns the size of the graph (edges)
int       graph_number_edges(const graph* g);
//!\brief Get the tag of a vertex
vertex_tag graph_get_vertex_tag(const graph* g, const vertex* v);
//!\brief Set the tag of a vertex
int       graph_set_vertex_tag(graph* g, vertex* v, vertex_tag vt);
//!\brief free the memory used for the graph
void      graph_free(graph* g);

#define DFS_STOP 1
#define DFS_CONTINUE 0
#define DFS_SKIPVERTEX 2
//!\brief Depth first search. It is a generic Graph traversal.
//!\parameter[in] f is a function which is applied to every vertex.
//!For every vertex it can return DFS_STOP to stop the traversal,
//!DFS_CONTINUE to continue deeper in the graph or DFS_SKIPVERTEX to ignore the vertex and continue the traversal.
//!\parameter[in] data can be modified by f to store any informations about the graph or can store useful information for f.
int       graph_connex_dfs(graph* g, vertex* v, vertex_action f, void* data);
#endif
