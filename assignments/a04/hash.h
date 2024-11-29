#ifndef HASH_H
#define HASH_H

#define KEY_SIZE 20

typedef struct {
  char key[KEY_SIZE];
  int value;
} HASHDATA;

typedef struct node {
  char key[KEY_SIZE];
  int value;
  struct node *next;
} HASHNODE;

typedef struct {
  HASHNODE **hna;
  int size;
  int count;
} HASHTABLE;

/**
 * Hashes a key string to an integer using hash table's size to determine index.
 * Calculated by the sum of the character values modulo size of hash table.
 *
 * @param key - the input key string
 * @param size - the size of the hash table
 * @return the index of the key in the hash table
 */
int hash(char *key, int size);

/**
 * Creates a new hash table with a given size.
 *
 * @param size - the size of the hash table
 * @return a pointer to the new hash table
 */
HASHTABLE *new_hashtable(int size);

/**
 * Inserts a HASHDATA entry into the hash table, ensuring that entries within
 * each linked list are sorted by key.
 *
 * @param ht - the hash table to insert into
 * @param key - the key of the entry
 * @param value - the value of the entry
 * @return 0 if the key already exists, 1 if the key is
 * new
 */
int hashtable_insert(HASHTABLE *ht, char *key, int value);

/**
 * Searches for a key in the hash table and returns the value associated with
 * it.
 *
 * @param ht - the hash table to search
 * @param key - the key to search for
 * @return a pointer to the HASHNODE if found or NULL if not found
 */
HASHNODE *hashtable_search(HASHTABLE *ht, char *key);

/**
 * Deletes a key from the hash table.
 *
 * @param ht - the hash table to delete from
 * @param key - the key to delete
 * @return 0 if the key was not found, 1 if the key was deleted
 */
int hashtable_delete(HASHTABLE *ht, char *key);

/**
 * Deletes all nodes in the hash table, clears all linked lists, and resets the
 * count to zero.
 *
 * @param ht - a pointer to a pointer to the hash table
 */
void hashtable_clear(HASHTABLE **ht);

#endif // HASH_H
