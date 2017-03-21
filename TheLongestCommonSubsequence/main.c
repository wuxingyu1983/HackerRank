#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  unsigned int m, n;
  unsigned int * a, * b;

  scanf("%u %u", &n, &m);

  a = malloc(sizeof(unsigned int) * n);
  b = malloc(sizeof(unsigned int) * m);

  for (int i = 0; i < n; i ++) {
    scanf("%u", &a[i]);
  }

  for (int i = 0; i < m; i ++) {
    scanf("%u", &b[i]);
  }

  unsigned int * * l;
  l = malloc(sizeof(unsigned int *) * n);
  for (int i = 0; i < n; i ++) {
    l[i] = malloc(sizeof(unsigned int) * m);
    memset(l[i], 0, sizeof(unsigned int) * m);
  }

  unsigned char * * p;
  p = malloc(sizeof(unsigned char *) * n);
  for (int i = 0; i < n; i ++) {
    p[i] = malloc(sizeof(unsigned char) * m);
    memset(p[i], 0, sizeof(unsigned char) * m);
  }

  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < m; j ++) {
      if (a[i] == b[j]) {
        if (0 == i || 0 == j) {
          l[i][j] = 1;
        }
        else {
          l[i][j] = l[i - 1][j - 1] + 1;
        }
        p[i][j] = 2;
      }
      else {
        if (0 < i && 0 < j) {
          if (l[i][j - 1] < l[i - 1][j]) {
            l[i][j] = l[i - 1][j];
            p[i][j] = 1;
          }
          else {
            l[i][j] = l[i][j - 1];
            p[i][j] = 3;
          }
        }
        else if (0 < i) {
            l[i][j] = l[i - 1][j];
            p[i][j] = 1;
        }
        else if (0 < j) {
            l[i][j] = l[i][j - 1];
            p[i][j] = 3;
        }
      }
    }
  }

  unsigned int * res = malloc(sizeof(unsigned int) * l[n - 1][m - 1]);

  int c = n - 1, r = m - 1;
  unsigned int last = l[n - 1][m - 1] - 1;
  while (0 <= c && 0 <= r) {
    if (2 == p[c][r]) {
      res[last --] = a[c];
      c --;
      r --;
    }
    else if (1 == p[c][r]) {
      c --;
    }
    else {
      r --;
    }
  }

  for (int i = 0; i < l[n - 1][m - 1]; i ++) {
    printf("%u", res[i]);
    if (i < (l[n - 1][m - 1] - 1)) {
      printf(" ");
    }
    else {
      printf("\n");
    }
  }

  free(res);
  for (int i = 0; i < n; i ++) {
    free(p[i]);
    free(l[i]);
  }
  free(p);
  free(l);
  free(a);
  free(b);

  return 0;
}
