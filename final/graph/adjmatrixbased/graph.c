#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

GRAPH *init_graph(int vertex_count) {
  GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
  graph->vertex_count = vertex_count;
  for (int i = 0; i < vertex_count; i++) {
    for (int j = 0; j < vertex_count; j++) {
      graph->adjmatrix[i][j] = 0;
    }
  }
  return graph;
}

void add_edge(GRAPH *graph, int u, int v) { graph->adjmatrix[u][v] = 1; }

void remove_edge(GRAPH *graph, int u, int v) { graph->adjmatrix[u][v] = 0; }

void print_adjmatrix(GRAPH *graph) {
  for (int i = 0; i < graph->vertex_count; i++) {
    for (int j = 0; j < graph->vertex_count; j++) {
      printf("%d ", graph->adjmatrix[i][j]);
    }
    printf("\n");
  }
}

int is_edge(GRAPH *graph, int u, int v) { return graph->adjmatrix[u][v]; }

void free_graph(GRAPH *graph) { free(graph); }
