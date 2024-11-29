#ifndef AVL_H
#define AVL_H

typedef struct record {
  char name[20];
  float score;
} RECORD;

typedef struct avlnode {
  RECORD data;
  int height;
  struct avlnode *left;
  struct avlnode *right;
} AVLNODE;

/* Insert a node with the given record data into the AVL tree.
 *
 * @param rootp - pointer to pointer to the tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data);

/* Delete a node with data.name matching the given key from the AVL tree.
 *
 * @param rootp - pointer to pointer to the tree root.
 * @param key - key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *key);

/* Search the AVL tree by key name.
 *
 * @param root - pointer to the tree root.
 * @param name - key to match with data.name for search.
 * @return - pointer to the node if found, otherwise NULL.
 */
AVLNODE *avl_search(AVLNODE *root, char *name);

/* Clean the AVL tree.
 *
 * @param rootp - pointer to pointer to the tree root.
 */
void avl_clean(AVLNODE **rootp);

/* Get the height of the AVL tree.
 *
 * @param root - pointer to the root of the tree.
 * @return - the height value at the root.
 */
int height(AVLNODE *root);

/* Return the balance factor at the given node.
 *
 * @param np - pointer to the node of the tree.
 * @return - the balance factor at the node.
 */
int balance_factor(AVLNODE *np);

/* Perform a left rotation at a given node.
 *
 * @param np - pointer to the rotation node.
 * @return - pointer to the new root of the subtree.
 */
AVLNODE *rotate_left(AVLNODE *np);

/* Perform a right rotation at a given node.
 *
 * @param np - pointer to the rotation node.
 * @return - pointer to the new root of the subtree.
 */
AVLNODE *rotate_right(AVLNODE *np);

/* Count the number of nodes in the AVL tree.
 *
 * @param root - pointer to the root of the tree.
 * @return - the number of nodes in the tree.
 */
int avl_count_nodes(AVLNODE *root);

#endif // AVL_H
