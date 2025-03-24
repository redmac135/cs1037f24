#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
  int x;
  int y;
};

void foo(struct point *);

int main() {
  struct point p1[] = {1, 2, 3, 4};
  foo(p1);
}

void foo(struct point p[]) { printf("%d\n", p[1].x); }
