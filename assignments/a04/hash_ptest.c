#include "hash.h"
#include <stdio.h>

int main() {
  HASHTABLE *ht = new_hashtable(10);
  hashtable_insert(ht, "apple", 1);
  hashtable_insert(ht, "banana", 2);
  hashtable_insert(ht, "cherry", 3);
  hashtable_insert(ht, "date", 4);
  hashtable_insert(ht, "elderberry", 5);
  hashtable_insert(ht, "fig", 6);
  hashtable_insert(ht, "grape", 7);
  hashtable_insert(ht, "honeydew", 8);
  hashtable_insert(ht, "kiwi", 9);
  hashtable_insert(ht, "lemon", 10);
  hashtable_insert(ht, "mango", 11);
  hashtable_insert(ht, "nectarine", 12);
  hashtable_insert(ht, "orange", 13);
  hashtable_insert(ht, "pear", 14);
  hashtable_insert(ht, "quince", 15);
  hashtable_insert(ht, "raspberry", 16);
  hashtable_insert(ht, "strawberry", 17);
  hashtable_insert(ht, "tangerine", 18);
  hashtable_insert(ht, "ugli", 19);
  hashtable_insert(ht, "vanilla", 20);
  hashtable_insert(ht, "watermelon", 21);
  hashtable_insert(ht, "ximenia", 22);
  hashtable_insert(ht, "yuzu", 23);
  hashtable_insert(ht, "zucchini", 24);

  HASHNODE *hn = hashtable_search(ht, "apple");
  printf("apple: %d\n", hn->value);
  hn = hashtable_search(ht, "banana");
  printf("banana: %d\n", hn->value);
  hn = hashtable_search(ht, "cherry");
  printf("cherry: %d\n", hn->value);
  hn = hashtable_search(ht, "date");
  printf("date: %d\n", hn->value);
  hn = hashtable_search(ht, "elderberry");
  printf("elderberry: %d\n", hn->value);
  hn = hashtable_search(ht, "fig");
  printf("fig: %d\n", hn->value);

  printf("clearing table ---\n");
  hashtable_clear(&ht);
  printf("table cleared\n");

  hn = hashtable_search(ht, "grape");
  printf("grape: %d\n", hn ? hn->value : -1);
  hn = hashtable_search(ht, "honeydew");
  printf("honeydew: %d\n", hn ? hn->value : -1);

  return 0;
}
