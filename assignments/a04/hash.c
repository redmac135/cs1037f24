#include "hash.h"
#include <stdlib.h>
#include <string.h>

int hash(char *key, int size) {
  int sum = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    sum += key[i];
  }
  return sum % size;
}

HASHTABLE *new_hashtable(int size) {
  HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
  ht->hna = (HASHNODE **)malloc(size * sizeof(HASHNODE *));
  for (int i = 0; i < size; i++) {
    ht->hna[i] = NULL;
  }
  ht->size = size;
  ht->count = 0;
  return ht;
}

int hashtable_insert(HASHTABLE *ht, char *key, int value) {
  HASHNODE *new_node = (HASHNODE *)malloc(sizeof(HASHNODE));

  strcpy(new_node->key, key);
  new_node->value = value;
  new_node->next = NULL;

  int index = hash(key, ht->size);
  HASHNODE *current = ht->hna[index];

  if (current == NULL) {
    ht->hna[index] = new_node;
    ht->count++;
    return 1;
  }

  HASHNODE *prev = NULL;
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      // if already exists, return 0
      return 0;
    }
    if (strcmp(current->key, key) > 0) {
      break;
    }
    prev = current;
    current = current->next;
  }

  // case where new_node is the new head
  if (prev == NULL) {
    new_node->next = ht->hna[index];
    ht->hna[index] = new_node;
  } else {
    // case where new_node is in the middle or end
    new_node->next = current;
    prev->next = new_node;
  }

  ht->count++;
  return 1;
}

HASHNODE *hashtable_search(HASHTABLE *ht, char *key) {
  int index = hash(key, ht->size);
  HASHNODE *current = ht->hna[index];

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

int hashtable_delete(HASHTABLE *ht, char *key) {
  int index = hash(key, ht->size);
  HASHNODE *current = ht->hna[index];
  HASHNODE *prev = NULL;

  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      if (prev == NULL) {
        ht->hna[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      ht->count--;
      return 1;
    }
    prev = current;
    current = current->next;
  }

  return 0;
}

void hashtable_clear(HASHTABLE **ht) {
  for (int i = 0; i < (*ht)->size; i++) {
    HASHNODE *current = (*ht)->hna[i];
    while (current != NULL) {
      HASHNODE *temp = current;
      current = current->next;
      free(temp);
    }
    (*ht)->hna[i] = NULL;
  }

  (*ht)->count = 0;

  return;
}
