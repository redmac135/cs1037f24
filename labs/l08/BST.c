#include "BST.h"

Node *addNode(Node *root, int value) {
  // case where tree is empty
  if (isEmpty(root)) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }

  // check where value belongs
  if (value < root->data) {
    if (root->left == NULL) {
      Node *newNode = (Node *)malloc(sizeof(Node));
      newNode->data = value;
      newNode->left = NULL;
      newNode->right = NULL;
      root->left = newNode;
    } else {
      addNode(root->left, value);
    }
  } else if (value > root->data) {
    if (root->right == NULL) {
      Node *newNode = (Node *)malloc(sizeof(Node));
      newNode->data = value;
      newNode->left = NULL;
      newNode->right = NULL;
      root->right = newNode;
    } else {
      addNode(root->right, value);
    }
  }

  return root;
}

Node *deleteNode(Node *root, int value) {
  // base case
  if (isEmpty(root)) {
    return root;
  }

  if (root->data == value) {
    // case 1: node has no children
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    }

    // case 2: node has one child
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    // case 3: node has two children
    Node *temp = findSmallestValue(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }

  // search for the node to delete
  Node *prev = NULL;
  Node *current = root;
  while (current != NULL && current->data != value) {
    prev = current;
    if (value < current->data)
      current = current->left;
    else if (value > current->data)
      current = current->right;
    else
      break;
  }

  // node not found
  if (current == NULL)
    return root;

  // case 1: node has no children
  if (current->left == NULL && current->right == NULL) {
    // case where this is the root node
    if (prev == NULL) {
      free(current);
      return NULL;
    }

    if (prev->left == current)
      prev->left = NULL;
    else
      prev->right = NULL;
    free(current);
  }
}

Node *searchNode(Node *root, int value) { return NULL; }

int computeSize(Node *root) { return 0; }

void inOrderTraversal(Node *root) {}

void postOrderTraversal(Node *root) {}

void visit(Node *node) {
  if (node != NULL)
    printf("%d ", node->data);
}

Node *findSmallestValue(Node *root) {
  Node *current = root;
  while (current && current->left != NULL)
    current = current->left;
  return current;
}
int isEmpty(Node *root) { return root == NULL; }
