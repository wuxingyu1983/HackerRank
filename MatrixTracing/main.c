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

  unsigned int i;
  for (i = prime; max >= i; i = i * prime) {
    ret += max / i;
  }

  return ret;
}

int main() {

  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int t;
  int i,j;
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
/*
  clock_t start;
  start = clock();
  printf("start at %fs\n", (double)start / CLOCKS_PER_SEC);
*/
  // 找到 max_m 以内所有的质数
  char *primes = malloc(max_mn * sizeof(char));
  memset(primes, 1, max_mn);

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
        printf("the count of %d is %d\n", p, c);
        unsigned int k;
        for (k = 0; k < c; k ++) {
          res = res * (unsigned long long)p % 1000000007;
        }
        printf("the res is %llu\n", res);
      }
    }
    printf("%llu\n", res);
  }

  free(primes);
  free(nms);
/*
  clock_t end;
  end = clock();
  printf("end at %fs\n", (double)end / CLOCKS_PER_SEC);
*/
  return 0;
}
