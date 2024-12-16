#include "mway_tree.h"
#include <stdio.h>

int main() {
  TNODE *root = NULL;

  printf("Test: Insert and Display\n");
  printf("insert_key(root, 22)\n");
  insert_key(&root, 22);
  printf("insert_key(root, 11)\n");
  insert_key(&root, 11);
  printf("insert_key(root, 33)\n");
  insert_key(&root, 33);
  display_tree(root);

  printf("\nTest: Search\n");
  printf("search_key(root, 22) = %d\n", search_key(root, 22));
  printf("search_key(root, 11) = %d\n", search_key(root, 11));
  printf("search_key(root, 33) = %d\n", search_key(root, 33));
  printf("search_key(root, 44) = %d\n", search_key(root, 44));

  printf("\nTest: In-order Traversal\n");
  print_inorder(root);

  printf("\nTest: Delete\n");
  printf("delete_key(&root, 22)\n");
  delete_key(&root, 22);
  display_tree(root);
  printf("delete_key(&root, 11)\n");
  delete_key(&root, 11);
  display_tree(root);
  printf("delete_key(&root, 33)\n");
  delete_key(&root, 33);
  display_tree(root);

  return 0;
}
