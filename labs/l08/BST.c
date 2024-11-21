#include "BST.h"

Node *addNode(Node *root, int value) {
  // case where tree is empty
  if (isEmpty(root)) {
    return createNode(value);
  }

  // check where value belongs
  if (value < root->data) {
    if (root->left == NULL) {
      Node *newNode = createNode(value);
      root->left = newNode;
    } else {
      addNode(root->left, value);
    }
  } else if (value > root->data) {
    if (root->right == NULL) {
      Node *newNode = createNode(value);
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
  if (value < root->data) {
    root->left = deleteNode(root->left, value);
  } else {
    root->right = deleteNode(root->right, value);
  }

  return root;
}

Node *searchNode(Node *root, int value) {
  if (isEmpty(root)) {
    return NULL;
  }

  if (root->data == value) {
    return root;
  }

  if (value < root->data) {
    return searchNode(root->left, value);
  } else {
    return searchNode(root->right, value);
  }
}

int computeSize(Node *root) {
  // base case
  if (isEmpty(root)) {
    return 0;
  }

  // recursively compute the size of the left and right subtrees
  return 1 + computeSize(root->left) + computeSize(root->right);
}

void inOrderTraversal(Node *root) {
  // if root is NULL, do nothing
  if (root != NULL) {
    // traverse left-root-right
    inOrderTraversal(root->left);
    visit(root);
    inOrderTraversal(root->right);
  }
  return;
}

void postOrderTraversal(Node *root) {
  // if root is NULL, do nothing
  if (root != NULL) {
    // traverse left-right-root
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    visit(root);
  }
  return;
}

void preOrderTraversal(Node *root) {
  // if root is NULL, do nothing
  if (root != NULL) {
    // traverse root-left-right
    visit(root);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
  }
  return;
}

void visit(Node *node) {
  if (node != NULL)
    printf("%d ", node->data);
}

Node *createNode(int value) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node *findSmallestValue(Node *root) {
  Node *current = root;
  while (current && current->left != NULL)
    current = current->left;
  return current;
}

int isEmpty(Node *root) { return root == NULL; }
