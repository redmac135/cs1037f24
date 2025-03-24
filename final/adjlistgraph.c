typedef struct adjnode {
  int id;
  int weight;
  struct adjnode *next;
} ADJNODE;

typedef struct node {
  int id;
  ADJNODE *neighbor;
  struct node *next;
} NODE;

typedef struct graph {
  int order;
  NODE *start;
} GRAPH;

#include <stdlib.h>

int get_max_weight(GRAPH g) {
  int max_weight = 0;
  NODE *n = g.start;
  while (n != NULL) {
    ADJNODE *a = n->neighbor;
    while (a != NULL) {
      if (a->weight > max_weight)
        max_weight = a->weight;
      a = a->next;
    }
    n = n->next;
  }
  return max_weight;
}
