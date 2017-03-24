#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define modulo 100000007

int main() {
  unsigned int t;

  scanf("%u", &t);

  unsigned int * n, * m;
  n = malloc(sizeof(unsigned int) * t);
  m = malloc(sizeof(unsigned int) * t);

  for (int i = 0; i < t; i ++) {
    scanf("%u %u", &n[i], &m[i]);
  }

  for (int i = 0; i < t; i ++) {
    unsigned int n_i = n[i];
    unsigned int m_i = m[i];
    unsigned int s = n_i / 2;
    unsigned long long * a = malloc(sizeof(unsigned long long) * n_i);
    unsigned long long * b = malloc(sizeof(unsigned long long) * (s + 1));
    unsigned long long sum;
    unsigned long long tmp;

    // init
    tmp = 0;
    for (int j = 0; j < s; j ++) {
      if (s < (j + 1) * 2) {
        a[j] = n_i - (j + 1) * 2 + 1;
      }
      else {
        a[j] = n_i - s;
      }
      tmp += a[j];
      tmp = tmp % modulo;
      if (0 == j % 2) {
        b[j / 2] = tmp;
      }
    }

    for (int j = s; j < n_i; j ++) {
      a[j] = n_i - s;
      tmp += a[j];
      tmp = tmp % modulo;
      if (0 == j % 2) {
        b[j / 2] = tmp;
      }
    }
    b[s] = tmp;   // sum

    for (int k = 0; k < m_i - 2; k ++) {
      tmp = 0;
      for (int j = 0; j < s; j ++) {
        a[j] = (b[s] + modulo - b[j]) % modulo;
        tmp += a[j];
        tmp = tmp % modulo;
        if (0 == j % 2) {
          b[j / 2] = tmp;
        }
      }

      for (int j = s; j < n_i; j ++) {
        a[j] = b[s];
        tmp += a[j];
        tmp = tmp % modulo;
        if (0 == j % 2) {
          b[j / 2] = tmp;
        }
      }
      b[s] = tmp;
    }

    printf("%llu\n", b[s]);

    free(b);
    free(a);
  }

  free(n);
  free(m);

  return 0;
}
