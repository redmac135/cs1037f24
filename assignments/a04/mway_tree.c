#include "mway_tree.h"
#include <stdio.h>
#include <stdlib.h>

TNODE *create_node() {
  TNODE *new_node = (TNODE *)malloc(sizeof(TNODE));
  new_node->count = 0;
  for (int i = 0; i < M; i++) {
    new_node->child[i] = NULL;
  }
  return new_node;
}

void insert_key(TNODE **root, int key) {
  // base case, tree empty
  if (*root == NULL) {
    *root = create_node();
    (*root)->key[0] = key;
    (*root)->count++;
    return;
  }

  TNODE *curr = *root;
  TNODE *prev = NULL;

  while (curr != NULL) {
    // check if there is room in the node
    if (curr->count < M - 1) {
      // find the correct position to insert the key
      for (int i = curr->count - 1; i >= 0; i--) {
        if (key > curr->key[i]) {
          // shift keys to the right
          for (int j = curr->count - 1; j > i; j--) {
            curr->key[j + 1] = curr->key[j];
          }
          // assign key
          curr->key[i + 1] = key;
          break;
        } else if (i == 0) {
          // shift keys to the right
          for (int j = curr->count - 1; j >= 0; j--) {
            curr->key[j + 1] = curr->key[j];
          }
          // assign key
          curr->key[0] = key;
          break;
        }
      }

      curr->count++;
      return;
    }

    // otherwise, look for the correct child to traverse
    for (int i = curr->count - 1; i >= 0; i--) {
      if (key > curr->key[i]) {
        prev = curr;
        curr = curr->child[i + 1];

        // if curr is null, then create new node
        if (curr == NULL) {
          prev->child[i + 1] = create_node();
          curr = prev->child[i + 1];
          curr->key[0] = key;
          curr->count++;
          return;
        }

        break;
      } else if (i == 0) {
        prev = curr;
        curr = curr->child[i];

        if (curr == NULL) {
          prev->child[i] = create_node();
          curr = prev->child[i];
          curr->key[0] = key;
          curr->count++;
          return;
        }

        break;
      }
    }
  }
}

int search_key(TNODE *root, int key) {
  if (root == NULL) {
    return 0;
  }

  TNODE *curr = root;
  while (curr != NULL) {
    for (int i = 0; i < curr->count; i++) {
      if (key == curr->key[i]) {
        return 1;
      } else if (key > curr->key[i]) {
        curr = curr->child[i + 1];
        break;
      } else if (i == curr->count - 1) {
        curr = curr->child[i];
        break;
      }
    }
  }

  return 0;
}

void print_inorder(TNODE *root) {
  if (root == NULL) {
    return;
  }

  for (int i = 0; i < root->count; i++) {
    print_inorder(root->child[i]);
    printf("%d ", root->key[i]);
  }
  print_inorder(root->child[root->count]);
}

void display_tree(TNODE *root) {
  if (root == NULL) {
    return;
  }

  printf("Node keys: [");
  for (int i = 0; i < root->count; i++) {
    printf("%d", root->key[i]);
    if (i < root->count - 1) {
      printf(", ");
    }
  }
  printf("]\n");

  printf("Child pointers: [");
  for (int i = 0; i < M; i++) {
    if (root->child[i] != NULL) {
      printf("%d", root->child[i]->key[0]);
    } else {
      printf("NULL");
    }
    if (i < M - 1) {
      printf(", ");
    }
  }
  printf("]\n");
}

// deletion helper: gets in-order predecessor
int get_inorder_predecessor(TNODE *root) {
  TNODE *curr = root;
  while (curr->child[curr->count] != NULL) {
    curr = curr->child[curr->count];
  }
  return curr->key[curr->count - 1];
}

// deletion helper: gets in-order successor
int get_inorder_successor(TNODE *root) {
  TNODE *curr = root;
  while (curr->child[0] != NULL) {
    curr = curr->child[0];
  }
  return curr->key[0];
}

// deletion helper: merges two nodes
void merge_nodes(TNODE **root, TNODE *parent, int index) {
  TNODE *left = parent->child[index];
  TNODE *right = parent->child[index + 1];

  // move key from parent to left
  left->key[left->count] = parent->key[index];
  left->count++;

  // move keys from right to left
  for (int i = 0; i < right->count; i++) {
    left->key[left->count] = right->key[i];
    left->count++;
  }

  // move child pointers from right to left
  for (int i = 0; i <= right->count; i++) {
    left->child[left->count] = right->child[i];
    left->count++;
  }

  // shift keys in parent to the left
  for (int i = index; i < parent->count - 1; i++) {
    parent->key[i] = parent->key[i + 1];
  }

  // shift child pointers in parent to the left
  for (int i = index + 1; i < parent->count; i++) {
    parent->child[i] = parent->child[i + 1];
  }

  // free right node
  free(right);
  parent->count--;
}

// deletion helper: borrow from previous child
void borrow_from_prev(TNODE *root, TNODE *parent, int index) {
  TNODE *child = parent->child[index];
  TNODE *prev_child = parent->child[index - 1];

  // shift keys in child to the right
  for (int i = child->count - 1; i >= 0; i--) {
    child->key[i + 1] = child->key[i];
  }

  // shift child pointers in child to the right
  for (int i = child->count; i >= 0; i--) {
    child->child[i + 1] = child->child[i];
  }

  // assign key from parent to child
  child->key[0] = parent->key[index - 1];
  child->count++;

  // assign key from prev_child to parent
  parent->key[index - 1] = prev_child->key[prev_child->count - 1];

  // assign child pointer from prev_child to child
  child->child[0] = prev_child->child[prev_child->count];

  // decrement counts
  prev_child->count--;
}

// deletion helper: borrow from next child
void borrow_from_next(TNODE *root, TNODE *parent, int index) {
  TNODE *child = parent->child[index];
  TNODE *next_child = parent->child[index + 1];

  // assign key from parent to child
  child->key[child->count] = parent->key[index];
  child->count++;

  // assign key from next_child to parent
  parent->key[index] = next_child->key[0];

  // shift keys in next_child to the left
  for (int i = 1; i < next_child->count; i++) {
    next_child->key[i - 1] = next_child->key[i];
  }

  // shift child pointers in next_child to the left
  for (int i = 1; i <= next_child->count; i++) {
    next_child->child[i - 1] = next_child->child[i];
  }

  // decrement counts
  next_child->count--;
}

// deletion helper: find index of key in node
int find_key(TNODE *root, int key) {
  for (int i = 0; i < root->count; i++) {
    if (key == root->key[i]) {
      return i;
    }
  }
  return -1;
}

// deletion helper: is leaf node
int is_leaf(TNODE *root) {
  int count = 0;
  for (int i = 0; i < M; i++) {
    if (root->child[i] != NULL) {
      count++;
    }
  }

  if (count == 0) {
    return 1;
  } else {
    return -1;
  }
}

int delete_key(TNODE **root, int key) {
  int idx = find_key(*root, key);

  if (idx != -1) {
    TNODE *curr = *root;

    // case 1: leaf node
    if (is_leaf(curr) != -1) {
      for (int i = idx; i < curr->count - 1; i++) {
        curr->key[i] = curr->key[i + 1];
      }
      curr->count--;
      return 1;
    }

    // case 2: internal node
    if (is_leaf(curr) == -1) {
      // find in-order predecessor
      int pred = get_inorder_predecessor(curr->child[idx]);
      curr->key[idx] = pred;
      delete_key(&curr->child[idx], pred);
      return 1;
    }
  } else {
    TNODE *curr = *root;
    TNODE *parent = NULL;
    int index = 0;

    // find the node to delete
    while (curr != NULL) {
      for (int i = 0; i < curr->count; i++) {
        if (key == curr->key[i]) {
          parent = curr;
          index = i;
          break;
        } else if (key > curr->key[i]) {
          curr = curr->child[i + 1];
          break;
        } else if (i == curr->count - 1) {
          curr = curr->child[i];
          break;
        }
      }
    }

    // case 3: key not found
    if (parent == NULL) {
      return 0;
    }

    // case 4: key is in a leaf node
    if (is_leaf(parent) != -1) {
      for (int i = index; i < parent->count - 1; i++) {
        parent->key[i] = parent->key[i + 1];
      }
      parent->count--;
      return 1;
    }

    // case 5: key is in an internal node
    if (is_leaf(parent) == -1) {
      TNODE *left_child = parent->child[index];
      TNODE *right_child = parent->child[index + 1];

      // case 5a: left child has enough keys
      if (left_child->count > M / 2) {
        borrow_from_prev(*root, parent, index);
        delete_key(&left_child, key);
        return 1;
      }

      // case 5b: right child has enough keys
      if (right_child->count > M / 2) {
        borrow_from_next(*root, parent, index);
        delete_key(&right_child, key);
        return 1;
      }

      // case 5c: merge left and right children
      merge_nodes(root, parent, index);
      delete_key(&left_child, key);
      return 1;
    }
  }

  return 0;
}
