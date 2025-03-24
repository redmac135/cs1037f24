#include "letter.c"
#include <stdio.h>

int main() {
  char str[] = "BINARY digits";
  LETTER letter = hot_letter(str);
  printf("The most frequent letter is '%c' with %d occurrences.\n", letter.le,
         letter.count);
  return 0;
}
