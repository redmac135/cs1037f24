
#ifndef ADJMATRIXBASED_GRAPH_H
#define ADJMATRIXBASED_GRAPH_H

#define MAX_VERTICES 20
#define MAX_EDGES 20

typedef struct {
  int vertex_count;
  int adjmatrix[MAX_VERTICES][MAX_VERTICES];
} GRAPH;

/**
 * Initialize the graph.
 *
 * @param vertex_count number of vertices in the graph
 * @return pointer to the graph
 */
GRAPH *init_graph(int vertex_count);

/**
 * Add an edge to the graph.
 *
 * @param graph pointer to the graph
 * @param u source vertex
 * @param v destination vertex
 */
void add_edge(GRAPH *graph, int u, int v);

/**
 * Remove an edge from the graph.
 *
 * @param graph pointer to the graph
 * @param u source vertex
 * @param v destination vertex
 */
void remove_edge(GRAPH *graph, int u, int v);

/**
 * Print the adjacency matrix of the graph.
 *
 * @param graph pointer to the graph
 */
void print_adjmatrix(GRAPH *graph);

/**
 * Check if there is an edge between two vertices.
 *
 * @param graph pointer to the graph
 * @param u source vertex
 * @param v destination vertex
 * @return 1 if there is an edge, 0 otherwise
 */
int is_edge(GRAPH *graph, int u, int v);

/**
 * Free the memory allocated for the graph.
 *
 * @param graph pointer to the graph
 */
void free_graph(GRAPH *graph);

#endif // 2DARRAYBASED_GRAPH_H
