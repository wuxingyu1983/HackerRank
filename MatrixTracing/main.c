#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

struct nm {
  unsigned int n;
  unsigned int m;
};

unsigned int pcount(unsigned int prime, unsigned int max) {
  unsigned int ret = 0;

  unsigned long long i;
  for (i = prime; max >= i; i = i * prime) {
    ret += max / i;
  }

  return ret;
}

int main() {

  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  unsigned int t;
  unsigned int i,j;
  struct nm *nms;

  scanf("%d", &t);

  nms = malloc(t * sizeof(struct nm));

  unsigned int max_mn = 1;
  for (i = 0; i< t; i++) {
    unsigned int n, m;
    scanf("%u %u", &n, &m);
    struct nm *curr = &(nms[i]);
    if (m > n ) {
      curr->n = m - 1;
      curr->m = n - 1;
    }
    else {
      curr->n = n - 1;
      curr->m = m - 1;
    }
    if ((m + n - 2) > max_mn) {
      max_mn = m + n -2;
    }
  }

  // 找到 max_m 以内所有的质数
  unsigned char *primes = malloc(max_mn * sizeof(unsigned char));
  memset(primes, 1, max_mn * sizeof(unsigned char));

  for (i = 2; i <= max_mn; i++) {
    if (primes[i - 1]) {
      for (j = 2; i * j <= max_mn; j++) {
        primes[i * j - 1] = 0;
      }
    }
  }

  unsigned int n, m;
  for (i = 0; i < t; i++) {
    struct nm *curr = &(nms[i]);
    n = curr->n;
    m = curr->m;

    unsigned long long res = 1;
    unsigned int p;
    for (p = 2; p <= m + n; p ++) {
      if (primes[p - 1]) {
        // 质数
        unsigned int c = pcount(p, n + m) - pcount(p, n) - pcount(p, m);
        unsigned int k;
        for (k = 0; k < c; k ++) {
          res = res * p % 1000000007;
        }
      }
    }
    printf("%llu\n", res);
  }

  free(primes);
  free(nms);

  return 0;
}
