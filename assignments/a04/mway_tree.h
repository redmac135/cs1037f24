#ifndef MWAY_TREE_H
#define MWAY_TREE_H

#define M 3

typedef struct node {
  int count; // number of keys in node
  int key[M - 1];
  struct node *child[M];
} TNODE;

/**
 * Allocates memory for a new m-way tre node.
 * Initializes key count to 0 and child pointers to NULL.
 *
 * @return pointer to the new node
 */
TNODE *create_node();

/**
 * Inserts a key into the m-way tree while maintaing sorted order.
 *
 * @param root - pointer to the root of the m-way tree
 * @param key - key to insert
 */
void insert_key(TNODE **root, int key);

/**
 * Searches for a key in the m-way tree.
 *
 * @param root - pointer to the root of the m-way tree
 * @param key - key to search for
 * @return 1 if key is found, 0 otherwise
 */
int search_key(TNODE *root, int key);

/**
 * Performs an in-order traversal of the m-way tree.
 * Prints the keys in sorted order.
 *
 * @param root - pointer to the root of the m-way tree
 */
void print_inorder(TNODE *root);

/**
 * Displays the tree structure, showing keys and their respective child
 * pointers.
 *
 * @param root - pointer to the root node
 */
void display_tree(TNODE *root);

/**
 * Deletes a key from the m-way tree and rebalances it if necessary.
 *
 * @param root - pointer to the root node
 * @param key - key to delete
 * @return - 1 if key is deleted, 0 otherwise
 */
int delete_key(TNODE **root, int key);

#endif // MWAY_TREE_H
