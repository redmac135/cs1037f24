typedef struct node {
  int key;  // Key of the node
  int data; // Data stored in the node
  struct node *left, *right;
} TNODE;

#include <stdlib.h>

void delete_min(TNODE **rootp) {
  TNODE *p, *parent;
  if (*rootp == NULL)
    return;
  p = *rootp;
  parent = NULL;
  while (p->left != NULL) {
    parent = p;
    p = p->left;
  }
  if (parent == NULL) {
    *rootp = p->right;
  } else {
    parent->left = p->right;
  }
  free(p);
}
