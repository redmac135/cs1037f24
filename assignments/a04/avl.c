#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new AVL node
AVLNODE *create_node(RECORD data) {
  AVLNODE *new_node = (AVLNODE *)malloc(sizeof(AVLNODE));
  if (!new_node) {
    fprintf(stderr, "Memory allocation failed for new node.\n");
    exit(EXIT_FAILURE); // Exit if memory allocation fails
  }
  new_node->data = data;
  new_node->height = 1; // New node is initially added at leaf
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

// Function to get the height of the tree
int height(AVLNODE *root) { return root ? root->height : 0; }

// Function to get the balance factor of a node
int balance_factor(AVLNODE *np) {
  return np ? height(np->left) - height(np->right) : 0;
}

// Perform a left rotation
AVLNODE *rotate_left(AVLNODE *np) {
  AVLNODE *new_root = np->right;
  AVLNODE *temp = new_root->left;

  new_root->left = np;
  np->right = temp;

  np->height = 1 + (height(np->left) > height(np->right) ? height(np->left)
                                                         : height(np->right));
  new_root->height = 1 + (height(new_root->left) > height(new_root->right)
                              ? height(new_root->left)
                              : height(new_root->right));

  return new_root;
}

// Perform a right rotation
AVLNODE *rotate_right(AVLNODE *np) {
  AVLNODE *new_root = np->left;
  AVLNODE *temp = new_root->right;

  new_root->right = np;
  np->left = temp;

  np->height = 1 + (height(np->left) > height(np->right) ? height(np->left)
                                                         : height(np->right));
  new_root->height = 1 + (height(new_root->left) > height(new_root->right)
                              ? height(new_root->left)
                              : height(new_root->right));

  return new_root;
}

// Insert a node into the AVL tree
void avl_insert(AVLNODE **rootp, RECORD data) {
  if (*rootp == NULL) {
    *rootp = create_node(data);
    return;
  }

  if (strcmp(data.name, (*rootp)->data.name) < 0) {
    avl_insert(&(*rootp)->left, data);
  } else if (strcmp(data.name, (*rootp)->data.name) > 0) {
    avl_insert(&(*rootp)->right, data);
  } else {
    // Duplicate names are not allowed
    fprintf(stderr, "Duplicate name '%s' not allowed.\n", data.name);
    return;
  }

  (*rootp)->height = 1 + (height((*rootp)->left) > height((*rootp)->right)
                              ? height((*rootp)->left)
                              : height((*rootp)->right));

  int balance = balance_factor(*rootp);

  // Left Left Case
  if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) < 0) {
    *rootp = rotate_right(*rootp);
    return;
  }

  // Right Right Case
  if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) > 0) {
    *rootp = rotate_left(*rootp);
    return;
  }

  // Left Right Case
  if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) > 0) {
    (*rootp)->left = rotate_left((*rootp)->left);
    *rootp = rotate_right(*rootp);
    return;
  }

  // Right Left Case
  if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) < 0) {
    (*rootp)->right = rotate_right((*rootp)->right);
    *rootp = rotate_left(*rootp);
    return;
  }
}

// Delete a node from the AVL tree
void avl_delete(AVLNODE **rootp, char *key) {
  if (*rootp == NULL) {
    fprintf(stderr, "Cannot delete: tree is empty.\n");
    return;
  }

  if (strcmp(key, (*rootp)->data.name) < 0) {
    avl_delete(&(*rootp)->left, key);
  } else if (strcmp(key, (*rootp)->data.name) > 0) {
    avl_delete(&(*rootp)->right, key);
  } else {
    // Node with only one child or no child
    if ((*rootp)->left == NULL || (*rootp)->right == NULL) {
      AVLNODE *temp = (*rootp)->left ? (*rootp)->left : (*rootp)->right;

      if (temp == NULL) {
        temp = *rootp;
        *rootp = NULL;
      } else {
        **rootp = *temp; // Copy the contents of the non-empty child
      }
      free(temp);
    } else {
      // Node with two children: Get the inorder successor (smallest in the
      // right subtree)
      AVLNODE *temp = (*rootp)->right;
      while (temp->left != NULL) {
        temp = temp->left;
      }

      // Copy the inorder successor's data to this node
      (*rootp)->data = temp->data;

      // Delete the inorder successor
      avl_delete(&(*rootp)->right, temp->data.name);
    }
  }

  if (*rootp == NULL) {
    return;
  }

  (*rootp)->height = 1 + (height((*rootp)->left) > height((*rootp)->right)
                              ? height((*rootp)->left)
                              : height((*rootp)->right));

  int balance = balance_factor(*rootp);

  // Left Left Case
  if (balance > 1 && balance_factor((*rootp)->left) >= 0) {
    *rootp = rotate_right(*rootp);
    return;
  }

  // Left Right Case
  if (balance > 1 && balance_factor((*rootp)->left) < 0) {
    (*rootp)->left = rotate_left((*rootp)->left);
    *rootp = rotate_right(*rootp);
    return;
  }

  // Right Right Case
  if (balance < -1 && balance_factor((*rootp)->right) <= 0) {
    *rootp = rotate_left(*rootp);
    return;
  }

  // Right Left Case
  if (balance < -1 && balance_factor((*rootp)->right) > 0) {
    (*rootp)->right = rotate_right((*rootp)->right);
    *rootp = rotate_left(*rootp);
    return;
  }
}

// Search for a node in the AVL tree
AVLNODE *avl_search(AVLNODE *root, char *name) {
  if (root == NULL) {
    return NULL;
  }

  if (strcmp(root->data.name, name) == 0) {
    return root;
  }

  if (strcmp(name, root->data.name) < 0) {
    return avl_search(root->left, name);
  }

  return avl_search(root->right, name);
}

// Clean the AVL tree
void avl_clean(AVLNODE **rootp) {
  if (*rootp) {
    avl_clean(&(*rootp)->left);
    avl_clean(&(*rootp)->right);
    free(*rootp);
    *rootp = NULL;
  }
}

// Function to print the AVL tree in-order
void avl_print_in_order(AVLNODE *root) {
  if (root) {
    avl_print_in_order(root->left);
    printf("Name: %s, Score: %.2f\n", root->data.name, root->data.score);
    avl_print_in_order(root->right);
  }
}

// Function to count the number of nodes in the AVL tree
int avl_count_nodes(AVLNODE *root) {
  if (root == NULL) {
    return 0;
  }
  return 1 + avl_count_nodes(root->left) + avl_count_nodes(root->right);
}

// Function to find the minimum node in the AVL tree
AVLNODE *avl_find_min(AVLNODE *root) {
  if (root == NULL) {
    return NULL;
  }
  while (root->left != NULL) {
    root = root->left;
  }
  return root;
}

// Function to find the maximum node in the AVL tree
AVLNODE *avl_find_max(AVLNODE *root) {
  if (root == NULL) {
    return NULL;
  }
  while (root->right != NULL) {
    root = root->right;
  }
  return root;
}

// Function to check if the AVL tree is balanced
int avl_is_balanced(AVLNODE *root) {
  if (root == NULL) {
    return 1; // An empty tree is balanced
  }
  int balance = balance_factor(root);
  return (balance >= -1 && balance <= 1) && avl_is_balanced(root->left) &&
         avl_is_balanced(root->right);
}
