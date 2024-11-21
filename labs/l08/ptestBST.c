#include "BST.h"

int main() {
  Node *root = NULL;

  // add example data
  // 26 - 9 - 32 - 3 - 13 - 28 - 40 - 1 - 4
  root = addNode(root, 26);
  root = addNode(root, 9);
  root = addNode(root, 32);
  root = addNode(root, 3);
  root = addNode(root, 13);
  root = addNode(root, 28);
  root = addNode(root, 40);
  root = addNode(root, 1);
  root = addNode(root, 4);

  // traverse the tree
  printf("Traverse InOrder: ");
  inOrderTraversal(root);

  printf("\nTraverse PostOrder: ");
  postOrderTraversal(root);

  printf("\nTraverse PreOrder: ");
  preOrderTraversal(root);

  // number of nodes
  printf("\nNumber of nodes in the tree is: %d\n", computeSize(root));

  // Test node existence
  printf("The number 13 is in the tree: %s\n",
         searchNode(root, 13) ? "true" : "false");
  printf("The number 15 is in the tree: %s\n",
         searchNode(root, 15) ? "true" : "false");

  // final postOrder traversal
  root = deleteNode(root, 26);
  printf("PostOrder traversal after deleting node 26 from tree is: ");
  postOrderTraversal(root);

  return 0;
}
