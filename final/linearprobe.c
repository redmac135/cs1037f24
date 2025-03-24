typedef struct {
  int *keys;     // Array to store keys
  void **values; // Array to store corresponding values
  int size;      // Total size of the hash table
  int count;     // Number of elements currently in the hash table
} HashTable;

#include <stdlib.h>

int resize_hash_table(HashTable *table, int new_size) {
  if (new_size <= table->count) {
    return 0;
  }

  HashTable *new_table = malloc(sizeof(HashTable));

  if (new_table == NULL) {
    return 0;
  }

  new_table->keys = malloc(sizeof(int) * new_size);

  if (new_table->keys == NULL) {
    free(new_table);
    return 0;
  }

  new_table->values = malloc(sizeof(void *) * new_size);

  if (new_table->values == NULL) {
    free(new_table->keys);
    free(new_table);
    return 0;
  }

  // rehash all keys with new size
  for (int i = 0; i < table->size; i++) {
    if (table->keys[i] != 0) {
      int index = table->keys[i] % new_size;
      while (new_table->keys[index] != 0) {
        index = (index + 1) % new_size;
      }
      new_table->keys[index] = table->keys[i];
      new_table->values[index] = table->values[i];
    }
  }

  free(table->keys);
  free(table->values);
  free(table);

  table = new_table;

  return 1;
}
