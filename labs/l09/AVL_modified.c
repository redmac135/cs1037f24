#include "AVL_modified.h"
#include <stdio.h>
#include <stdlib.h>

AVLNode *deleteNode(AVLNode *root, int key) {
  // Base case
  if (root == NULL) {
    return root;
  }

  // Recurse down the tree
  if (key < root->key) {
    root->left = deleteNode(root->left, key); // Assign the result
  } else if (key > root->key) {
    root->right = deleteNode(root->right, key); // Assign the result
  } else {
    // Node to be deleted found
    if (root->left == NULL || root->right == NULL) {
      // One or no child
      AVLNode *temp = root->left ? root->left : root->right;
      free(root);
      return temp;
    } else {
      // Node with two children
      AVLNode *min = root->right;
      while (min->left != NULL) {
        min = min->left;
      }
      root->key = min->key;
      root->right = deleteNode(root->right, min->key);
    }
  }

  // Update height
  root->height = 1 + max(height(root->left), height(root->right));

  // Get balance
  int balance = getBalance(root);

  // Balance the tree
  if (balance > 1 && getBalance(root->left) >= 0) {
    return rightRotate(root); // Left Left Case
  }
  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left); // Left Right Case
    return rightRotate(root);
  }
  if (balance < -1 && getBalance(root->right) <= 0) {
    return leftRotate(root); // Right Right Case
  }
  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right); // Right Left Case
    return leftRotate(root);
  }

  return root;
}

// Create a new node
AVLNode *createNode(int key) {
  AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
  node->key = key;
  node->height = 1;
  node->left = node->right = NULL;
  return node;
}

// Function to get the height of a node
int height(AVLNode *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

AVLNode *search(AVLNode *root, int key) {
  if (root == NULL || root->key == key) {
    return root;
  }

  if (root->key < key) {
    return search(root->right, key);
  }

  return search(root->left, key);
}

void incrementHeight(AVLNode *root) {
  if (root == NULL) {
    return;
  }

  root->height++;
  incrementHeight(root->left);
  incrementHeight(root->right);
}

void preOrder(AVLNode *root) {
  if (root != NULL) {
    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(AVLNode *root) {
  if (root != NULL) {
    inOrder(root->left);
    printf("%d ", root->key);
    inOrder(root->right);
  }
}

int countNodes(AVLNode *root) {
  // base case
  if (root == NULL) {
    return 0;
  }

  return 1 + countNodes(root->left) + countNodes(root->right);
}

void levelOrder(AVLNode *root) {
  if (root == NULL) {
    return;
  }

  // Create array based queue to store nodes
  AVLNode **queue =
      (AVLNode **)malloc(sizeof(AVLNode *) * (power(2, root->height) + 1));
  AVLNode **front = queue;
  AVLNode **rear = queue + 1;

  // Enqueue the root
  *front = root;

  while (front != rear) {
    AVLNode *node = *front;
    front++;

    if (node->left != NULL) {
      *rear = node->left;
      rear++;
    }

    if (node->right != NULL) {
      *rear = node->right;
      rear++;
    }

    printf("%d ", node->key);
  }

  return;
}

int power(int base, int exp) {
  int result = 1;
  for (int i = 0; i < exp; i++) {
    result *= base;
  }
  return result;
}

void tree_free(AVLNode *root) {
  if (root == NULL) {
    return;
  }

  tree_free(root->left);
  tree_free(root->right);
  free(root);
}

// Utility function to get the maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// Right rotate subtree rooted with y
AVLNode *rightRotate(AVLNode *y) {
  AVLNode *x = y->left;
  AVLNode *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  // Return new root
  return x;
}

// Left rotate subtree rooted with x
AVLNode *leftRotate(AVLNode *x) {
  AVLNode *y = x->right;
  AVLNode *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  // Return new root
  return y;
}

// Get the balance factor of a node
int getBalance(AVLNode *node) {
  if (node == NULL)
    return 0;
  return height(node->left) - height(node->right);
}

// Insert a node in the AVL tree and balance the tree
AVLNode *insert(AVLNode *node, int key) {
  // Perform the normal BST insertion
  if (node == NULL)
    return createNode(key);

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else // Equal keys are not allowed in AVL Tree
    return node;

  // Update the height of this ancestor node
  node->height = 1 + max(height(node->left), height(node->right));

  // Get the balance factor of this ancestor node to check if it became
  // unbalanced
  int balance = getBalance(node);

  // If this node becomes unbalanced, then there are 4 cases

  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // Return the (unchanged) node pointer
  return node;
}

int main() {
  AVLNode *root = NULL;

  // Insert nodes into the AVL tree
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 10);
  root = insert(root, 25);
  root = insert(root, 5); // This will trigger rotations

  // Print the pre-order traversal of the AVL tree
  printf("In-order traversal after insertions: ");
  inOrder(root);
  printf("\n");

  // Remove minimum
  root = deleteNode(root, 5);

  // Print the pre-order traversal of the AVL tree
  printf("Minimum value removed: 5\n");

  // Print the in-order traversal after deletion
  printf("In-order traversal after deletion: ");
  inOrder(root);
  printf("\n");

  // Remove 20
  root = deleteNode(root, 20);

  // Print the in-order traversal after deleting 20
  printf("In-order traversal after deleting 20: ");
  inOrder(root);

  return 0;
}
