#ifndef AVL_MODIFIED_H
#define AVL_MODIFIED_H

#include <stdio.h>
#include <stdlib.h>

// Define the AVLNode structure
typedef struct AVLNode {
  int key;
  int height;
  struct AVLNode *left;
  struct AVLNode *right;
} AVLNode;

/**
 * Creates a new node with the given key.
 *
 * @param key The key of the new node.
 * @return The new node.
 */
AVLNode *createNode(int key);

/**
 * Inserts a value into the AVL tree and rebalances if necessary.
 *
 * @param node The root of the AVL tree.
 * @param key The key to insert.
 * @return The new root of the AVL tree.
 */
AVLNode *insert(AVLNode *node, int key);

/**
 * Deletes a node from the AVL tree and rebalances if necessary.
 *
 * @param root The root of the AVL tree.
 * @param key The key of the node to delete.
 * @return The new root of the AVL tree.
 */
AVLNode *deleteNode(AVLNode *root, int key);

/**
 * Searches for a node with a given key in the AVL tree.
 *
 * @param root The root of the AVL tree.
 * @param key The key to search for.
 * @return The node with the given key, or NULL if it is not found.
 */
AVLNode *search(AVLNode *root, int key);

/**
 * Increments the height for the node and all child nodes.
 *
 * @param root The root to begin incrementing height.
 */
void incrementHeight(AVLNode *root);

/**
 * Prints the value of each node when the tree is traversed in pre-order.
 *
 * @param root The root of the AVL tree.
 */
void preOrder(AVLNode *root);

/**
 * Prints the value of each node when the tree is traversed in-order.
 *
 * @param root The root of the AVL tree.
 */
void inOrder(AVLNode *root);

/**
 * Returns the height of a given node.
 *
 * @param node The node to get the height of.
 * @return The height of the node.
 */
int height(AVLNode *node);

/**
 * Returns the balance factor of a given node.
 *
 * @param node The node to get the balance factor of.
 * @return The balance factor of the node.
 */
int getBalance(AVLNode *node);

/**
 * Count the number of nodes in the AVL tree.
 *
 * @param root The root of the AVL tree.
 * @return The number of nodes in the AVL tree.
 */
int countNodes(AVLNode *root);

/**
 * Prints the value of each node when the tree is traversed in level-order.
 *
 * @param root The root of the AVL tree.
 */
void levelOrder(AVLNode *root);

/**
 * Raises a base to a given power through iteration.
 *
 * @param base The base.
 * @param exp The exponent.
 * @return The result of raising the base to the exponent.
 */
int power(int base, int exp);

/**
 * Frees the memory allocated for the AVL tree.
 *
 * @param root The root of the AVL tree.
 */
void tree_free(AVLNode *root);

/**
 * Returns the maximum of two integers.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The maximum of the two integers.
 */
int max(int a, int b);

/**
 * Right rotates the subtree rooted with y.
 *
 * @param y The root of the subtree to rotate.
 * @return The new root of the subtree.
 */
AVLNode *rightRotate(AVLNode *y);

/**
 * Left rotates the subtree rooted with x.
 *
 * @param x The root of the subtree to rotate.
 * @return The new root of the subtree.
 */
AVLNode *leftRotate(AVLNode *x);

#endif // AVL_MODIFIED_H
