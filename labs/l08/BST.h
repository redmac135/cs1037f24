#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

// Node structure for the binary search tree
typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

// Function prototypes
/**
 * Adds a new node with the given value to the tree.
 * @param root Pointer to the root node of the tree.
 * @param value The value to add to the tree.
 * @return Pointer to the root node after insertion.
 */
Node *addNode(Node *root, int value);

/**
 * Deletes the node with the given value from the tree.
 * @param root Pointer to the root node of the tree.
 * @param value The value to delete from the tree.
 * @return Pointer to the root node after deletion.
 */
Node *deleteNode(Node *root, int value);

/**
 * Searches for a node with the given value in the tree.
 * @param root Pointer to the root node of the tree.
 * @param value The value to search for.
 * @return Pointer to the found node or NULL if not found.
 */

Node *searchNode(Node *root, int value);
/**
 * Computes the number of nodes in the tree.
 * @param root Pointer to the root node of the tree.
 * @return The total number of nodes in the tree.
 */

int computeSize(Node *root);
/**
 * Performs an in-order traversal of the tree.
 * @param root Pointer to the root node of the tree.
 */

void inOrderTraversal(Node *root);

/**
 * Performs a post-order traversal of the tree.
 * @param root Pointer to the root node of the tree.
 */
void postOrderTraversal(Node *root);

/**
 * Performs a pre-order traversal of the tree.
 * @param root Pointer to the root node of the tree.
 */
void preOrderTraversal(Node *root);

/**
 * Helper function to print the value of a node.
 * @param node Pointer to the node to visit.
 */
void visit(Node *node);

/**
 * Finds the node with the smallest value in a subtree.
 * @param root Pointer to the root of the subtree.
 * @return Pointer to the node with the smallest value.
 */
Node *findSmallestValue(Node *root);

/**
 * Checks if the tree is empty.
 * @param root Pointer to the root node of the tree.
 * @return 1 if the tree is empty, 0 otherwise.
 */
int isEmpty(Node *root);

#endif // BST_H
