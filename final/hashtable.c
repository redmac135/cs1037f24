#include <stdio.h>

int hash(int key) { return (5 * key + 3) % 13; }

int main() {
  int hashtable[13] = {0};

  // hash values 2 4 6 7 15 13 19 23 with linear probing
  int keys[] = {2, 4, 6, 7, 15, 13, 19, 23};

  for (int i = 0; i < 8; i++) {
    int key = keys[i];
    int index = hash(key);
    while (hashtable[index] != 0) {
      index = (index + 1) % 13;
    }
    hashtable[index] = key;
  }

  // print the hashtable
  for (int i = 0; i < 13; i++) {
    printf("%d ", hashtable[i]);
  }
}
