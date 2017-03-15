#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void proc(unsigned int * d, unsigned int a, unsigned int len) {
  unsigned int start = 0;
  unsigned int end = len - 1;
  unsigned int middle;

  while (end > start) {
    middle = (start + end) / 2;
    if (d[middle] < a) {
      start = middle + 1;
    }
    else {
      end = middle;
    }
  }

  d[end] = a;
}

int main() {
  unsigned int n;
  scanf("%u", &n);

  unsigned int len = 0;
  unsigned int * d;
  d = malloc(sizeof(unsigned int) * n);
  memset(d, 0, sizeof(unsigned int) * n);

  for (int i = 0; i < n; i ++) {
    unsigned int a;
    scanf("%u", &a);

    if (0 == i) {
      d[0] = a;
      len ++;
    }
    else {
      if (a < d[0]) {
        d[0] = a;
      }
      else if (a > d[len - 1]) {
        d[len] = a;
        len ++;
      }
      else {
        proc(d, a, len);
      }
    }
  }

  free(d);

  printf("%u\n", len);

  return 0;
}
