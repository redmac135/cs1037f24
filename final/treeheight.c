typedef struct node {
  int data;
  struct node *left, *right;
} TNODE;

#include <stdlib.h>

// iteratively, no recursion
int tree_height(TNODE *root) {
  if (root == NULL)
    return -1;

  // declare a stack
  TNODE *stack[1000] = {NULL};
  int depths[1000] = {0};
  int top = -1;

  // push the root node
  stack[++top] = root;
  int max_depth = 0;
  int depth;

  while (top >= 0) {
    TNODE *node = stack[top];
    depth = depths[top--];

    if (depth > max_depth)
      max_depth = depth;

    if (node->right != NULL) {
      stack[++top] = node->right;
      depths[top] = depth + 1;
    }
    if (node->left != NULL) {
      stack[++top] = node->left;
      depths[top] = depth + 1;
    }
  }

  return max_depth;
}
