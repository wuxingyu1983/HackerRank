#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  unsigned int n;
  unsigned int m;

  scanf("%u %u", &n, &m);

  long long *array;
  array = malloc(n * sizeof(long long));
  memset(array, 0, n * sizeof(long long));

  long long *brray;
  brray = malloc(n * sizeof(long long));
  memset(brray, 0, n * sizeof(long long));

  for (unsigned int i = 0; i < m; i++) {
    unsigned int a, b, k;

    scanf("%u %u %u", &a, &b, &k);

    array[a - 1] += k;
    brray[b - 1] += k;
  }

  unsigned long long max = 0, tmp = 0;
  for (unsigned int i = 0; i < n; i++) {
    if (array[i]) {
      tmp += array[i];
    }
    if (brray[i]) {
      if (tmp > max)
      {
        max = tmp;
      }
      tmp -= brray[i];
    }
  }

  printf("%llu\n", max);

  free(array);

  return 0;
}
