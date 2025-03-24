typedef struct letter {
  char le;
  int count;
} LETTER;

LETTER hot_letter(char *str) {
  // declare hash table
  int hashtable[26] = {0};

  // count the frequency of each letter
  while (*str != '\0') {
    if (*str >= 'a' && *str <= 'z') {
      hashtable[*str - 'a']++;
    } else if (*str >= 'A' && *str <= 'Z') {
      hashtable[*str - 'A']++;
    } else {
      // ignore other characters
    }
    str++;
  }

  // find the most frequent letter
  int max = 0;
  int index = 0;
  for (int i = 0; i < 26; i++) {
    if (hashtable[i] > max) {
      max = hashtable[i];
      index = i;
    }
  }

  // return the most frequent letter
  LETTER letter;
  letter.le = 'a' + index;
  letter.count = max;

  return letter;
}
